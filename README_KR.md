# Minishell
> Bash와 유사한 동작을 수행하는 Unix Shell 구현 프로젝트

- Language : C
- Environment : Linux (Ubuntu)
- Team Size : 1
- Development Period : 2026.3.17 ~ 2026.5.18

명령어 실행, 파이프라인, 리디렉션, 환경변수 확장, heredoc, signal 처리 등을 지원합니다.

# 왜 만들었는가
Bash의 동작 원리를 이해하기 위해 직접 Shell을 구현했습니다.

명령어가 입력된 이후 토큰화, 확장, 파싱, 실행 과정을 직접 구현하면서 Unix 프로세스와 Shell의 내부 동작을 학습하는 것을 목표로 했습니다.

# 빌드 및 실행
```bash
make
./minishell
```

# 구현 기능
본 프로젝트는 Bash의 주요 동작을 참고하여 구현되었으며,
환경변수 확장, heredoc, signal 처리, exit status 등 Bash와의 동작 호환성을 고려하여 개발했습니다.

- Pipe (|)
- Input Redirection (<)
- Output Redirection (>)
- Append Redirection (>>)
- Heredoc (<<)
- Environment Variable Expansion ($VAR)
- Exit Status Expansion ($?)
- Builtin Commands
    - echo
    - cd
    - pwd
    - export
    - unset
    - env
    - exit
- Signal Handling (SIGINT, SIGQUIT)

# 사용 예시
```bash
minishell$ echo hello | cat
hello

minishell$ echo $HOME
/home/user

minishell$ echo hello > file
minishell$ cat file
hello

minishell$ cat << EOF
hello
EOF
hello
```

# 아키텍처 설계 의도

프로젝트는 각 단계의 책임을 분리하기 위해

- Lexer
- Expander
- Parser
- Executor

구조로 설계했습니다.

문자열 해석, 명령어 구조 생성, 명령어 실행을 분리함으로써 각 단계가 하나의 책임만 가지도록 구성했습니다.

# 구조
```text
사용자 입력
    ↓
Lexer
    ↓
Token List
    ↓
Expander
    ↓
Expanded Tokens
    ↓
Parser
    ↓
Command List
    ↓
Executor
    ↓
Builtin / External Command
```

## lexer
Lexer는 입력 문자열을 토큰으로 분리합니다.

파이프(|)와 리디렉션(<, >, <<, >>)은 명령어 구조에 직접적인 영향을 주기 때문에 별도의 토큰으로 분리합니다.

또한 quote 내부의 공백은 인자 구분에 사용되지 않으므로 quote 상태를 추적하며 토큰화를 수행합니다.

## expander
Expander는 문자열 확장을 담당합니다.

- 환경변수 확장 ($VAR)
- 종료 상태 확장 ($?)
- quote 제거

를 수행합니다.

Bash와 동일하게

- single quote('') 내부에서는 확장을 수행하지 않습니다.
- double quote("") 내부에서는 환경변수 확장을 수행합니다.

환경변수 확장 결과는 명령어 구조에 영향을 줄 수 있으므로 Parser 이전 단계에서 확장을 수행하도록 설계했습니다.

## parser
Parser는 토큰을 실제 명령어 구조로 변환합니다.

이 단계에서는

- 파이프 문법 검사
- 리디렉션 문법 검사
- 명령어 구조 생성

을 수행합니다.

Parser 결과로 연결 리스트 기반의 command 구조체가 생성되며,

- argv
- fd_in
- fd_out
- redirection 정보

등 실행에 필요한 정보가 저장됩니다.

## executor
Executor는 Parser가 생성한 command 리스트를 실행합니다.

파이프와 리디렉션을 적용한 뒤 명령어를 실행합니다.

실행 방식은 명령어 종류에 따라 달라집니다.

### Builtin 실행
- cd
- export
- unset
- exit

와 같이 shell 상태를 변경하는 builtin은 부모 프로세스에서 실행합니다.

자식 프로세스에서 실행하면 부모 shell의 상태가 변경되지 않기 때문입니다.

### External Command 실행
일반 명령어는 fork 후 자식 프로세스에서 실행합니다.

실행 시 PATH 탐색 후 execve를 호출합니다.

### Pipeline 실행
파이프라인에서는 Bash와 동일하게 모든 명령어를 자식 프로세스에서 실행합니다.

pipe와 dup2를 이용하여 각 프로세스의 입출력을 연결합니다.

# 트러블 슈팅

## Heredoc Signal 처리

### 문제

Heredoc 입력 중 Ctrl+C를 입력하면 Heredoc만 중단되어야 하지만, 초기 구현에서는 Shell 전체가 종료되거나 상태가 비정상적으로 변경되는 문제가 발생했습니다.

### 원인 분석

초기 구현에서는 Heredoc 입력을 Shell 프로세스에서 직접 처리하고 있었습니다.

이 경우 Heredoc 입력 중 발생한 SIGINT가 Shell 프로세스에도 전달되어 Shell 상태까지 영향을 받게 되었습니다.

### 해결

Heredoc 입력을 별도의 자식 프로세스에서 처리하도록 변경했습니다.

* Parent Process : Shell 유지
* Child Process : Heredoc 입력 처리

이후 SIGINT 발생 시 Child Process만 종료하고 Parent Shell은 계속 실행되도록 수정했습니다.

### 결과

* Ctrl+C 입력 시 Heredoc만 중단
* Shell은 정상적으로 다음 명령 입력 가능
* Bash와 동일한 동작 확인

### 배운 점

Signal 처리 시 어떤 프로세스가 Signal을 받아야 하는지 구분하는 것이 중요하다는 점을 배웠습니다.

또한 Bash가 Heredoc을 별도의 실행 흐름으로 처리하는 이유를 이해할 수 있었습니다.

## Non-interactive Heredoc 처리

### 문제

Heredoc을 child process에서 처리하도록 구현한 이후, 터미널에서 직접 입력하는 interactive 환경에서는 정상적으로 동작했지만 `printf ... | ./minishell`처럼 파이프로 입력이 들어오는 non-interactive 환경에서 heredoc 본문이 정상적으로 소비되지 않는 문제가 발생했습니다.

### 원인 분석

기존 구현에서는 heredoc 입력을 항상 child process에서 처리했습니다.

interactive 환경에서는 이 방식이 signal 처리와 readline 상태 분리에 유리했지만, non-interactive 환경에서는 문제가 되었습니다.

파이프로 입력이 들어오는 경우 `get_next_line()`이 표준 입력에서 여러 줄을 내부 static buffer에 미리 읽어둘 수 있습니다. 이 상태에서 `fork()`가 발생하면 child process가 heredoc 본문을 읽더라도 parent process의 `get_next_line()` buffer 상태에는 반영되지 않습니다.

그 결과 parent process가 heredoc 본문으로 소비되어야 할 줄을 이후 명령어 입력처럼 다시 처리하는 문제가 발생했습니다.

### 해결

`isatty(STDIN_FILENO)`를 사용해 입력 환경을 구분했습니다.

- TTY 환경에서는 기존처럼 child process에서 heredoc을 처리했습니다.
- Non-TTY 환경에서는 parent process에서 heredoc을 직접 읽도록 변경했습니다.

또한 heredoc 입력을 읽는 함수를 `read_heredoc_to_pipe()`로 분리하고, 입력 방식에 따라 `readline()` 또는 `get_next_line()`을 사용하도록 정리했습니다.

### 결과

- 터미널에서 직접 입력하는 interactive heredoc 정상 동작
- `printf ... | ./minishell` 형태의 non-interactive heredoc 정상 동작
- heredoc 본문이 이후 명령어로 잘못 처리되는 문제 해결

### 배운 점

표준 입력이 같아 보여도 TTY 입력과 파이프 입력은 처리 방식이 달라질 수 있다는 점을 배웠습니다.

특히 `fork()` 이후에는 parent와 child가 각각 독립된 메모리 상태를 가지므로, `get_next_line()`의 static buffer처럼 내부 상태를 가진 입력 함수는 프로세스 분리와 함께 사용할 때 주의가 필요하다는 점을 경험했습니다.

## Exit Status 처리

### 문제

외부 명령어와 Pipeline 실행 이후 `$?` 값이 Bash와 다르게 동작하는 문제가 발생했습니다.

명령어가 정상적으로 종료되었음에도 실패한 것으로 처리되거나, 자식 프로세스의 실제 종료 상태가 Shell에 올바르게 반영되지 않는 경우가 있었습니다.

### 원인 분석

초기 구현에서는 `waitpid()`로 자식 프로세스의 종료를 기다렸지만, 반환된 `status` 값을 충분히 해석하지 않고 있었습니다.

특히 Pipeline 종료 상태를 처리하는 코드에서는 Signal 종료만 고려하고 있었습니다.

```c
if (!WIFSIGNALED(status))
    return (1);
```

그 결과 정상 종료(`WIFEXITED`)한 경우에도 실제 종료 코드를 반환하지 못하고 항상 `1`을 반환했습니다.

또한 외부 명령어 실행 시에도 자식 프로세스의 종료 상태를 그대로 Shell 상태로 반영하지 못하는 문제가 있었습니다.

### 해결

`waitpid()`가 반환한 `status` 값을 다음과 같이 구분하여 처리하도록 수정했습니다.

```c
if (WIFEXITED(status))
    return (WEXITSTATUS(status));
```

정상 종료 시에는 실제 exit code를 반환하고,

```c
if (WIFSIGNALED(status))
    return (128 + WTERMSIG(status));
```

Signal 종료 시에는 Bash와 동일하게 `128 + signal number` 규칙을 적용했습니다.

이를 통해 외부 명령어와 Pipeline 모두 동일한 종료 상태 처리 로직을 사용하도록 정리했습니다.

### 결과

```bash
true | cat
echo $?
```

결과:

```text
0
```

```bash
false | cat
echo $?
```

결과:

```text
1
```

또한 외부 명령어 실행 시에도 실제 종료 상태가 `$?`에 올바르게 반영되도록 수정했습니다.

### 배운 점

프로세스를 실행하는 것과 프로세스의 종료 상태를 Shell 상태로 반영하는 것은 별개의 문제라는 점을 배웠습니다.

또한 Bash 호환성을 맞추기 위해서는 명령어 실행뿐 아니라 종료 상태 전파 방식까지 정확하게 구현해야 한다는 점을 경험했습니다.



# 배운 점
이 프로젝트를 통해 Unix Shell의 내부 동작을 이해할 수 있었습니다.

특히 다음 내용을 깊게 학습했습니다.

- fork와 execve를 이용한 프로세스 생성 및 실행
- pipe와 dup2를 이용한 프로세스 간 입출력 연결
- 부모/자식 프로세스의 역할 분리
- signal 처리 방식
- 파일 디스크립터 관리
- Bash의 환경변수 확장과 heredoc 동작
- Lexer, Expander, Parser, Executor로 책임을 분리하는 설계 방법
- 단순 기능 구현보다 Bash와의 동작 호환성을 맞추는 과정이 더 어렵다는 점을 경험했습니다.

