open State;
open Action;

let uplinkStart = (_uplinkState, sequence: Schema.commandSequence) => {
  ...initialUplinkState,
  sequenceId: Some(sequence##id),
  pending: List.map(c => c##id, sequence##commands),
  inProgress: true,
};

let uplinkSend = (uplinkState, id) => {
  let {pending, unresolved} = uplinkState;
  let isPending = List.exists(cId => cId == id, pending);
  let uplinkState = {
    ...uplinkState,
    pending: List.filter(cId => cId != id, pending),
    unresolved: isPending ? [id, ...unresolved] : unresolved,
  };

  let inProgress =
    List.length(uplinkState.pending)
    + List.length(uplinkState.unresolved) != 0;

  {...uplinkState, inProgress};
};

let uplinkTimeout = (uplinkState, id) => {
  let {unresolved, failed} = uplinkState;
  let isUnresolved = List.exists(cId => cId == id, unresolved);
  let uplinkState = {
    ...uplinkState,
    unresolved: List.filter(cId => cId != id, unresolved),
    failed: isUnresolved ? [id, ...failed] : failed,
  };

  let inProgress =
    List.length(uplinkState.pending)
    + List.length(uplinkState.unresolved) != 0;

  {...uplinkState, inProgress};
};

let uplinkStop = uplinkState => {...uplinkState, inProgress: false};

let reducer = (state: state, action: action) : state =>
  switch (action) {
  | UplinkStart(sequence) => {uplink: uplinkStart(state.uplink, sequence)}
  | UplinkSend(id) => {uplink: uplinkSend(state.uplink, id)}
  | UplinkTimeout(id) => {uplink: uplinkTimeout(state.uplink, id)}
  | UplinkAck(_id) => state
  | UplinkStop => {uplink: uplinkStop(state.uplink)}
  };