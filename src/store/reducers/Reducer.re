open State;
open Action;

let uplinkStart = (uplinkState: uplinkState, sequence: Schema.commandSequence) => {
  ...uplinkState,
  sequenceId: Some(sequence##id),
  pending: List.map(c => c##id, sequence##commands),
};

let uplinkSend = (uplinkState: uplinkState, id) => {
  let {pending, unresolved} = uplinkState;
  let isPending = List.exists(cId => cId == id, pending);
  {
    ...uplinkState,
    pending: List.filter(cId => cId != id, pending),
    unresolved: isPending ? [id, ...unresolved] : unresolved,
  };
};

let uplinkTimeout = (uplinkState: uplinkState, id) => {
  let {unresolved, failed} = uplinkState;
  let isUnresolved = List.exists(cId => cId == id, unresolved);
  {
    ...uplinkState,
    unresolved: List.filter(cId => cId != id, unresolved),
    failed: isUnresolved ? [id, ...failed] : failed,
  };
};

let reducer = (state: state, action: action) : state =>
  switch (action) {
  | UplinkStart(sequence) => {uplink: uplinkStart(state.uplink, sequence)}
  | UplinkSend(id) => {uplink: uplinkSend(state.uplink, id)}
  | UplinkTimeout(id) => {uplink: uplinkTimeout(state.uplink, id)}
  | UplinkAck(_id) => state
  };