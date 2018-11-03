type t('s, 'a) = {
  state: ref('s),
  reducer: ('s, 'a) => 's,
  observers: ref(list('s => unit)),
};

let create = (reducer, initialState) => {
  reducer,
  state: ref(initialState),
  observers: ref([]),
};

let dispatch = ({reducer, state, observers}, action) => {
  let newState = reducer(state^, action);
  state := newState;
  List.iter(obs => obs(newState), observers^);
};

let getState = store => store.state^;

/* TODO: change the implementation to return a unsubscribe function */
let subscribe = ({observers}, listener) =>
  observers := [listener, ...observers^];