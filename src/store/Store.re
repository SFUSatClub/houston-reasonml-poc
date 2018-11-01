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

let subscribe = ({observers}, listener) =>
  observers := [listener, ...observers^];