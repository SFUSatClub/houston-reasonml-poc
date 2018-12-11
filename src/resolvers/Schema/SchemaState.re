type state = {
  .
  "state": {
    .
    "uplink": {
      .
      "sequenceId": Js.Nullable.t(string),
      "pending": array(string),
      "unresolved": array(string),
      "successful": array(string),
      "failed": array(string),
      "inProgress": bool,
    },
  },
};