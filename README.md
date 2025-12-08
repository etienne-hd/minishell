# minishell [![wakatime](https://wakatime.com/badge/user/b5c6762d-cdfb-4336-9c84-87845f0e1976/project/ecc51af8-9625-4e80-af58-6781a42186a3.svg)](https://wakatime.com/badge/user/b5c6762d-cdfb-4336-9c84-87845f0e1976/project/ecc51af8-9625-4e80-af58-6781a42186a3)

*minishell is a 42 project: You must recreate a minimal version of bash.*

- **101/100** ✅

## Features
- Pipe (|)
- Environment variables
- Variable expansion
- Redirection (<, <<, >, >>)
- Built-in (echo, pwd, export, unset, env, exit)
- Signal (ctrl+C, ctrl+D, ctrl+\\)
- History

## Parsing

Parsing is the most complex part of **Minishell**.

We start by retrieving the user’s input with `readline`. Then we verify that all quotes are properly closed, and perform a pre-tokenization step using three token types: `[TEXT, REDIRECTION, PIPE]`.
From there, we apply a few simple syntax rules:

* `* ← REDIRECTION → TEXT`
* `* ← TEXT → *`
* `!START ← PIPE → REDIRECTION, TEXT`

Once the syntax is validated, we proceed with the final tokenization using these types: `[CMD, PIPE, IN_FILE, IN_HERE_DOC, OUT_FILE, OUT_FILE_APPEND]`.
We then join arguments, because two commands cannot appear consecutively without being separated by a pipe.

Next comes the most challenging part: **expansion**. You need to avoid expanding values that have already been expanded, while also removing quotes at the right moment.

Finally, we transform everything into a set of processes ready for execution.

> Illustration
![Illustration](/images/parsing.png)

![42](https://img.shields.io/badge/-42-black?style=for-the-badge&logo=42&logoColor=white)