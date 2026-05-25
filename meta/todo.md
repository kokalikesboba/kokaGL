### Adding a better rotation function to viewport class
 - [x] Clear out input.cpp's old method.

 There are a couple of reasons why I would want to do this. For one, the specific input mode setup only works on Wayland,
MacOS cannot rotate the camera at all. It also calculates math that should be internal to the viewport. viewport needs it's own setter.
This would allow it to stay mathematically consistent all the time,  as well as enable other modes  of input much better.
 