# Reducers

## Action

Action is an Enum and represents an event that affects the state

## State

State is a immutable struct that represents the state of the server at a specific point in time

- I defined the state as a ReasonML Struct.
- To pass the state to the client as part of the "state" subscription, we need to map it to a JS object.
  `serialize` returns a JS compatible type expected by the GraphQL

## Reducer

Reducer take a state and action and return a new state of the system

- (state, action) => state
