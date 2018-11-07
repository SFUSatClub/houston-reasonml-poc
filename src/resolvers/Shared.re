type store = Store.t(State.state, Action.action);

type unsubscribe = unit => unit;

type con = {
  write: string => bool,
  subscribe: (string => unit) => unsubscribe,
};

type dep = {
  store,
  con,
};