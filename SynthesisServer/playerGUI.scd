(
var playButton,pauseButton,stopButton,nextButton,previousButton,addButton,
    tracktitle,timeElapsed,volumeSlider,shuffleButton;

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
shuffleButton = Button.new().states([["Shuffle"]]);

w = Window.new(bounds: Rect(200,200,255,100)).layout_(
  VLayout(
    HLayout(
      timeElapsed,
      VLayout(
        tracktitle,
        volumeSlider,
        shuffleButton
      )
    ),
    HLayout(
      previousButton,
      playButton,
      pauseButton,
      stopButton,
      nextButton,
      addButton
    )
  )
);

w.front;
)
