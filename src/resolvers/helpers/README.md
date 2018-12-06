# Helpers

You should watch [Structuring JavaScript projects for testability](https://youtu.be/aL6SouuO0_k)

Helpers are JavaScript functions that are used by the Resolvers.

- `readJsonFile` parses the JSON file identified by the path into a JS object. This function returns a promise.
- `writeJsonFile` serializes a object to JSON and writes it to the specified path.
- `injectIdToObjTree` when we have a list of objects we need to somehow identify them.

  - we have a list of command sequences
  - each command sequence has a list of commands
  - each command has a list of arguments

  This function generates a hash of the information accessable from each object (sequences, commands, arguments) and injects this hash as an id into the object.

## Files

- `factory.js` implements the functions mentioned above and takes `fs` and `hash` as dependencies.
- `index.js` injects `fs` and `hash` dependencies
