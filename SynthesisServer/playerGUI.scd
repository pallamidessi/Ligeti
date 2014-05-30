/*
TODO: add constraints/bounds
*/
(
var playButton,pauseButton,stopButton,nextButton,previousButton,addButton,
    tracktitle,timeElapsed,volumeSlider,shuffleButton,trackList;

playButton = Button.new().states_([["Play"]]);
pauseButton = Button.new().states_([["Pause"]]);
stopButton = Button.new().states_([["Stop"]]);
nextButton = Button.new().states_([["Next"]]);
previousButton = Button.new().states_([["Previous"]]);
addButton = Button.new().states_([["Add"]]);

timeElapsed = StaticText.new().string_("00:00");
tracktitle = StaticText.new().string_("Artist - Tracktitle");
volumeSlider = Slider.new();
volumeSlider.orientation = \horizontal;
shuffleButton = Button.new().states_([["Shuffle"]]);
trackList=ListView.new().items=["Artist1 - Tracktitle1","Artist2 - Tracktitle2",
                              "Artist3 - Tracktitle3","Artist4 - Tracktitle4"];

w = Window.new(bounds: Rect(200,200,255,100)).layout_(
  VLayout(
    HLayout(
      timeElapsed,
      VLayout(
        tracktitle,
        HLayout(
          volumeSlider,
          shuffleButton
        )
      )
    ),
    HLayout(
      previousButton,
      playButton,
      pauseButton,
      stopButton,
      nextButton,
      addButton
    ),
    trackList;
  )
);

w.front;
)
