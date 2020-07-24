# AnimatedLEDStrip Client Library for C++

[![Build Status](https://travis-ci.com/AnimatedLEDStrip/client-cpp.svg?branch=master)](https://travis-ci.com/AnimatedLEDStrip/client-cpp)
[![codecov](https://codecov.io/gh/AnimatedLEDStrip/client-cpp/branch/master/graph/badge.svg)](https://codecov.io/gh/AnimatedLEDStrip/client-cpp)

This library allows a C++ 11 client to connect to an AnimatedLEDStrip server, allowing the client to send animations to the server and receive currently running animations from the server, among other information.

## Creating an `AnimationSender`
An `AnimationSender` is constructed with two arguments:
- `host`: The IP address of the server (as a c-style string)
- `port`: The port that the client should connect to (as an `int`)

```c++
AnimationSender sender("10.0.0.254", 5);
```

## Starting the `AnimationSender`
An `AnimationSender` is started by calling the `start()` method on the instance.
`start()` will return `0` if the connection is successful, `-1` if there is an error.

```c++
sender.start();
```

## Stopping the `AnimationSender`
To stop the `AnimationSender`, call its `end()` method.
`end()` will return `0` if the disconnection is successful, `-1` if there is an error.

```c++
sender.end();
```

## Sending Data
An animation can be sent to the server by creating an instance of the `AnimationData` struct, then calling `sendAnimation` with the struct as the argument.

```c++
ColorContainer cc;
cc.addColor(0xFF);
cc.addColor(0xFF00);

AnimationData data;
data.addColor(cc);

sender.sendAnimation(data);
```

#### `AnimationData` type notes
The C++ library uses the following values for `continuous` and `direction`:
- `continuous`: `DEFAULT`, `CONTINUOUS`, `NONCONTINUOUS`
- `direction`: `FORWARD`, `BACKWARD`

## Receiving Data
Received animations are saved to `runningAnimations`.

To retrieve an animation, use

```c++
sender.runningAnimations.[ID];
```

where `ID` is the string ID of the animation.
