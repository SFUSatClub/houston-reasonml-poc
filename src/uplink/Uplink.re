open Action;

type timerId;
[@bs.val] external setTimeout : (unit => unit, int) => timerId = "setTimeout";
[@bs.val] external clearTimeout : timerId => unit = "clearTimeout";

type store = Store.t(State.state, Action.action);

type t = {
  timers: ref(list(timerId)),
  store,
};

let create = store => {timers: ref([]), store};

let createTimers = (store, commands) => {
  let timeout = id => Store.dispatch(store, UplinkTimeout(id));
  let send = id => Store.dispatch(store, UplinkSend(id));

  let rec aux = (commands, acc) =>
    switch (commands) {
    | [] => []
    | [cmd, ...rest] =>
      let epoch = acc + cmd##wait;
      [
        setTimeout(() => send(cmd##id), epoch),
        setTimeout(() => timeout(cmd##id), epoch + cmd##timeout),
        ...aux(rest, acc + epoch),
      ];
    };

  aux(commands, 0);
};

let start = ({store, timers}, sequence) => {
  let uplinkState = Store.getState(store).uplink;
  uplinkState.inProgress ?
    () :
    {
      Store.dispatch(store, UplinkStart(sequence));
      timers := createTimers(store, sequence##commands);
    };
};

let stop = uplink => {
  List.iter(clearTimeout, uplink.timers^);
  uplink.timers := [];
};