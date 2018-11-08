open Action;

type timerId;
[@bs.val] external setTimeout : (unit => unit, int) => timerId = "setTimeout";
[@bs.val] external clearTimeout : timerId => unit = "clearTimeout";

type t = {
  timers: ref(list(timerId)),
  store: Shared.store,
  con: Shared.con,
};

let create: Shared.dep => t =
  dep => {timers: ref([]), store: dep.store, con: dep.con};

let createTimers = ({store, con}, commands) => {
  let timeout = id => Store.dispatch(store, UplinkTimeout(id));
  let send = id => {
    con.write(id) |> ignore;
    Store.dispatch(store, UplinkSend(id));
  };

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

let handle = data => Js.log(data);

let start = (dep, sequence) => {
  let {store, timers, con} = dep;
  let uplinkState = Store.getState(store).uplink;
  uplinkState.inProgress ?
    () :
    {
      Store.dispatch(store, UplinkStart(sequence));
      timers := createTimers(dep, sequence##commands);
      con.subscribe(handle) |> ignore;
    };
};

let stop = ({timers, store}) => {
  let uplinkState = Store.getState(store).uplink;
  uplinkState.inProgress ?
    {
      List.iter(clearTimeout, timers^);
      timers := [];
      Store.dispatch(store, UplinkStop);
    } :
    ();
};