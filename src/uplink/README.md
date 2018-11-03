# Uplink

Holds the actual logic for uplinking (executing) a command sequence.

- it takes `store` and `sequence` as arguments
- returns a tuple `(start, stop)`
  - `start` sets up timers to uplink the command sequence
  - `stop` stops the timers

It's important to note that the start function should only be called once

- TODO: refactor the module to remove the dependency on the state. With this we will only depend on the `state`
