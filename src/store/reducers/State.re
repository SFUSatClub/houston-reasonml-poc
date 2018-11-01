type uplinkState = {
  sequenceId: option(string),
  pending: list(string),
  unresolved: list(string),
  successful: list(string),
  failed: list(string),
  inProgress: bool,
};

let initialUplinkState = {
  sequenceId: None,
  pending: [],
  unresolved: [],
  successful: [],
  failed: [],
  inProgress: false,
};

[@bs.deriving jsConverter]
type state = {uplink: uplinkState};

let initialState = {uplink: initialUplinkState};