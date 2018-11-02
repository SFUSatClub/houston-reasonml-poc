open Action;

type store = Store.t(State.state, Action.action);

type timerId;
[@bs.val] external setTimeout : (unit => unit, int) => timerId = "setTimeout";
[@bs.val] external clearTimeout : timerId => unit = "clearTimeout";

let uplink = (store: store) => {
  let timeout = id => Store.dispatch(store, UplinkTimeout(id));
  let send = id => Store.dispatch(store, UplinkSend(id));

  sequence => {
    let timerIds = ref([]);

    let rec scheduleTimer = (commands, acc) =>
      switch (commands) {
      | [] => ()
      | [cmd, ...rest] =>
        let epoch = acc + cmd##wait;
        timerIds := [setTimeout(() => send(cmd##id), epoch), ...timerIds^];

        timerIds :=
          [
            setTimeout(() => timeout(cmd##id), epoch + cmd##timeout),
            ...timerIds^,
          ];

        scheduleTimer(rest, acc + epoch);
      };

    let start = () => {
      let uplinkState = Store.getState(store).uplink;
      uplinkState.inProgress ?
        () :
        {
          Store.dispatch(store, UplinkStart(sequence));
          scheduleTimer(sequence##commands, 0);
        };
    };

    let stop = () => List.iter(clearTimeout, timerIds^);

    (start, stop);
  };
};