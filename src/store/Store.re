type listener('s) = {
  id: int,
  call: 's => unit,
};

type t('s, 'a) = {
  state: ref('s),
  reducer: ('s, 'a) => 's,
  observers: ref(list(listener('s))),
  observerCount: ref(int),
};

type unsubscribe = unit => unit;

let create = (reducer, initialState) => {
  reducer,
  state: ref(initialState),
  observers: ref([]),
  observerCount: ref(0),
};

let dispatch = ({reducer, state, observers}, action) => {
  let newState = reducer(state^, action);
  state := newState;
  List.iter(obs => obs.call(newState), observers^);
};

let getState = store => store.state^;

let subscribe = ({observers, observerCount}, call) => {
  let listener = {id: observerCount^, call};
  observers := [listener, ...observers^];
  let unsubscribe = () =>
    observers := List.filter(l => l.id != observerCount^, observers^);

  observerCount := observerCount^ + 1;

  unsubscribe;
};