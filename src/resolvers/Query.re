open Schema;
open Helpers;

/*
   Actual implementation of the root resolvers
   Note that the resolvers take "store" as a dependency. We inject a store value in the "Resolvers.re" file.
   Since non of the resolvers use the store value, we are ignoring it for now.
 */

let resolvers: query = {
  "findCommandSequence": (_root, args) => {
    let path = "src/command_sequence/" ++ args##id ++ ".json";
    readCommandSequence(path);
  },
};