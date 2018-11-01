open State;
open Action;

let uplinkStart = (uplinkState: uplinkState, sequence: Schema.commandSequence) => {
  ...uplinkState,
  sequenceId: Some(sequence##id),
  pending: List.map(c => c##id, sequence##commands),
};

let reducer = (state: state, action: action) : state =>
  switch (action) {
  | UplinkStart(sequence) => {uplink: uplinkStart(state.uplink, sequence)}
  | UplinkSend(_id) => state
  | UplinkAck(_id) => state
  | UplinkTimeout(_id) => state
  };