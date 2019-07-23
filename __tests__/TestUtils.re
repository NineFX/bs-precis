// wraps node functions for headless testing:
[@bs.val] [@bs.module "fs"]
external readFileSync: (string, [@bs.as "utf8"] _) => string = "readFileSync";
