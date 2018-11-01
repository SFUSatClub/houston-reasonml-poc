// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");

function uplinkStart(uplinkState, sequence) {
  return /* record */[
          /* sequenceId : Some */[sequence.id],
          /* pending */List.map((function (c) {
                  return c.id;
                }), sequence.commands),
          /* unresolved */uplinkState[/* unresolved */2],
          /* successful */uplinkState[/* successful */3],
          /* failed */uplinkState[/* failed */4],
          /* inProgress */uplinkState[/* inProgress */5]
        ];
}

function reducer(state, action) {
  if (action.tag) {
    return state;
  } else {
    return /* record */[/* uplink */uplinkStart(state[/* uplink */0], action[0])];
  }
}

exports.uplinkStart = uplinkStart;
exports.reducer = reducer;
/* No side effect */
