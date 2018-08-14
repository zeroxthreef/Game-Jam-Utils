# Game Jam Utilities

Utilities for making mini game engines for game jams like Ludum Dare.

## Compiling

```
mkdir build && cd build && cmake ..
make -j(cpu threads)
```

## Polling Events

If you are using something like SDL, do

```cpp
int poll_wrapper(){return SDL_PollEvent(&event);}
```

but do not use the event pointer passed to the state manager, use the original pointer, but keep the original SDL_Event variable the same.
