# SerialVariable
A library that communicates with the Arduino over Serial

The SerialVariable creates an array that can be written to over the serial monitor through the arduino IDE.

It is important that the update function is in your main loop and called.

A separate callback function is optional and needs an int argument which passes back the index that was last changed.

To select an index where to change a number at, send the index number (starting at 0) followed by a colon (:) i.e. index 12

12:

To then change the value at your index, send the new value followed by a semicolon i.e. 123

123;

Feel free to do so in one line as such

12:123;

If you are changing the value at the same index multiple times in a row you may do so in the same line or multiple lines as such

14:111;222;333;

or

14:

111;

222;

333;


If you forget to add a semicolon after hitting enter, simply send a semicolon as SerialVariable buffers the entire input until either a semicolon arrives

123

;

This is interpreted as 123

123

123;

This is interpreted as 123123
