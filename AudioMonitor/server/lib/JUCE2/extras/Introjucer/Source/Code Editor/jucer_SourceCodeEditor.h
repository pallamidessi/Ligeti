/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#ifndef __JUCER_SOURCECODEEDITOR_JUCEHEADER__
#define __JUCER_SOURCECODEEDITOR_JUCEHEADER__

#include "../Project/jucer_Project.h"
#include "../Application/jucer_DocumentEditorComponent.h"


//==============================================================================
class SourceCodeDocument  : public OpenDocumentManager::Document
{
public:
    SourceCodeDocument (Project*, const File&);

    bool loadedOk() const override                           { return true; }
    bool isForFile (const File& file) const override         { return getFile() == file; }
    bool isForNode (const ValueTree&) const override         { return false; }
    bool refersToProject (Project& p) const override         { return project == &p; }
    Project* getProject() const override                     { return project; }
    String getName() const override                          { return getFile().getFileName(); }
    String getType() const override                          { return getFile().getFileExtension() + " file"; }
    File getFile() const override                            { return modDetector.getFile(); }
    bool needsSaving() const override                        { return codeDoc != nullptr && codeDoc->hasChangedSinceSavePoint(); }
    bool hasFileBeenModifiedExternally() override            { return modDetector.hasBeenModified(); }
    void fileHasBeenRenamed (const File& newFile) override   { modDetector.fileHasBeenRenamed (newFile); }
    String getState() const override                         { return lastState != nullptr ? lastState->toString() : String::empty; }
    void restoreState (const String& state) override         { lastState = new CodeEditorComponent::State (state); }

    File getCounterpartFile() const override
    {
        const File file (getFile());

        if (file.hasFileExtension (sourceFileExtensions))
        {
            static const char* extensions[] = { "h", "hpp", "hxx", "hh", nullptr };
            return findCounterpart (file, extensions);
        }

        if (file.hasFileExtension (headerFileExtensions))
        {
            static const char* extensions[] = { "cpp", "mm", "cc", "cxx", "c", "m", nullptr };
            return findCounterpart (file, extensions);
        }

        return File::nonexistent;
    }

    static File findCounterpart (const File& file, const char** extensions)
    {
        while (*extensions != nullptr)
        {
            const File f (file.withFileExtension (*extensions++));

            if (f.existsAsFile())
                return f;
        }

        return File::nonexistent;
    }

    void reloadFromFile() override;
    bool save() override;
    bool saveAs() override;

    Component* createEditor() override;
    Component* createViewer() override       { return createEditor(); }

    void updateLastState (CodeEditorComponent&);
    void applyLastState (CodeEditorComponent&) const;

    CodeDocument& getCodeDocument();

    //==============================================================================
    struct Type  : public OpenDocumentManager::DocumentType
    {
        bool canOpenFile (const File& file) override
        {
            if (file.hasFileExtension (sourceOrHeaderFileExtensions)
                 || file.hasFileExtension ("txt;inc;tcc;xml;plist;rtf;html;htm;php;py;rb;cs"))
                return true;

            MemoryBlock mb;
            if (file.loadFileAsData (mb)
                 && seemsToBeText (static_cast <const char*> (mb.getData()), (int) mb.getSize())
                 && ! file.hasFileExtension ("svg"))
                return true;

            return false;
        }

        static bool seemsToBeText (const char* const chars, const int num) noexcept
        {
            for (int i = 0; i < num; ++i)
            {
                const char c = chars[i];
                if ((c < 32 && c != '\t' && c != '\r' && c != '\n') || chars[i] > 126)
                    return false;
            }

            return true;
        }

        Document* openFile (Project* p, const File& file) override   { return new SourceCodeDocument (p, file); }
    };

protected:
    FileModificationDetector modDetector;
    ScopedPointer<CodeDocument> codeDoc;
    Project* project;

    ScopedPointer<CodeEditorComponent::State> lastState;

    void reloadInternal();
};

//==============================================================================
class SourceCodeEditor  : public DocumentEditorComponent,
                          private ValueTree::Listener,
                          private CodeDocument::Listener
{
public:
    SourceCodeEditor (OpenDocumentManager::Document*, CodeDocument&);
    SourceCodeEditor (OpenDocumentManager::Document*, CodeEditorComponent*);
    ~SourceCodeEditor();

    void scrollToKeepRangeOnScreen (Range<int> range);
    void highlight (Range<int> range, bool cursorAtStart);

    ScopedPointer<CodeEditorComponent> editor;

private:
    void resized() override;

    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree&, ValueTree&) override;
    void valueTreeChildOrderChanged (ValueTree&) override;
    void valueTreeParentChanged (ValueTree&) override;
    void valueTreeRedirected (ValueTree&) override;

    void codeDocumentTextInserted (const String&, int) override;
    void codeDocumentTextDeleted (int, int) override;

    void setEditor (CodeEditorComponent*);
    void updateColourScheme();
    void checkSaveState();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SourceCodeEditor)
};


//==============================================================================
class GenericCodeEditorComponent  : public CodeEditorComponent
{
public:
    GenericCodeEditorComponent (const File&, CodeDocument&, CodeTokeniser*);
    ~GenericCodeEditorComponent();

    void addPopupMenuItems (PopupMenu&, const MouseEvent*) override;
    void performPopupMenuAction (int menuItemID) override;

    void getAllCommands (Array<CommandID>&) override;
    void getCommandInfo (CommandID, ApplicationCommandInfo&) override;
    bool perform (const InvocationInfo&) override;

    void showFindPanel();
    void hideFindPanel();
    void findSelection();
    void findNext (bool forwards, bool skipCurrentSelection);
    void handleEscapeKey() override;

    void resized() override;

    static String getSearchString()                 { return getAppSettings().getGlobalProperties().getValue ("searchString"); }
    static void setSearchString (const String& s)   { getAppSettings().getGlobalProperties().setValue ("searchString", s); }
    static bool isCaseSensitiveSearch()             { return getAppSettings().getGlobalProperties().getBoolValue ("searchCaseSensitive"); }
    static void setCaseSensitiveSearch (bool b)     { getAppSettings().getGlobalProperties().setValue ("searchCaseSensitive", b); }

private:
    File file;
    class FindPanel;
    ScopedPointer<FindPanel> findPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GenericCodeEditorComponent)
};

//==============================================================================
class CppCodeEditorComponent  : public GenericCodeEditorComponent
{
public:
    CppCodeEditorComponent (const File&, CodeDocument&);
    ~CppCodeEditorComponent();

    void addPopupMenuItems (PopupMenu&, const MouseEvent*) override;
    void performPopupMenuAction (int menuItemID) override;

    void handleReturnKey() override;
    void insertTextAtCaret (const String& newText) override;

private:
    void insertComponentClass();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CppCodeEditorComponent)
};


#endif   // __JUCER_SOURCECODEEDITOR_JUCEHEADER__
