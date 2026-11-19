# ConversorUC

Formata os códigos dentro das tags `<codigo_UC>` de arquivos XML para o padrao
`XXX.XXX.XXX-XX`, preservando o conteúdo das demais linhas do arquivo.

## Executaveis

| Arquivo | Tipo | Descricao |
|---|---|---|
| `ConversorUC_gui.exe` | Janela (GUI) | Interface grafica: arraste o XML para a janela, escolha o modo e clique em **Converter**. Sem janela preta de console. |
| `ConversorUC.exe` | Console (CLI) | Interface de linha de comando, comportamento identico ao anterior. |

### Modos disponiveis (nos dois)

1. **Simular** — mostra o que seria convertido; nada e alterado.
2. **Gerar novo XML** — grava o resultado em `<entrada>_CPF.xml` (editavel na GUI).
3. **Alterar (backup)** — substitui o original e cria `<entrada>.bak`.

### Atalhos da CLI

```
ConversorUC [-i | -o saida.xml] [-q] [-n | --dry-run] [--] entrada.xml
```

Codigos de saida: `0` ok, `1` falha, `2` uso incorreto, `3` concluido com avisos.

## Como compilar

### Requisitos

O script usa as ferramentas GNU (`as`, `gcc`, `ld`, `objcopy`) e **nao funciona
em um Prompt de Comando puro do Windows sem toolchain**. Escolha uma opcao:

| Opcao | Como instalar | Como rodar |
|---|---|---|
| **WSL** (testado) | `wsl --install -d Debian` e, dentro do WSL: `sudo apt install -y build-essential python3` | Abra a pasta do projeto (ex.: `cd /mnt/c/Users/.../mistral-ai-main/mistral-ai-main`) e rode `python3 build.py` |
| **MSYS2** | [msys2.org](https://www.msys2.org); no shell UCRT64: `pacman -S mingw-w64-ucrt-x86_64-toolchain` | Rode `python build.py` dentro do shell UCRT64 |
| **Toolchain proprio** | qualquer GCC/binutils com suporte a PE (pei-x86-64) | defina `TOOL_PREFIX` (ex.: `set TOOL_PREFIX=x86_64-w64-mingw32-`) |

### Gerar os executaveis

```
python3 build.py
```

Se alguma ferramenta faltar no PATH, o script mostra instrucoes de instalacao em
vez de um traceback. Os exes gerados rodam no Windows nativo (nao precisam do WSL).

O script gera `ConversorUC.exe` (console) e `ConversorUC_gui.exe` (janela).

## Estrutura

```
uc_core.h            tipos Counts/LogBuf e prototipos do nucleo
uc_core.c            logica de conversao/busca das tags + utilitarios de backup/nome de saida
ConversorUC.c        CLI (entry point `start`, modo console)
ConversorUC_gui.c    interface grafica Win32 (entry point `start`, modo janela)
build.py             gera ambos os PE (tabela de imports escrita a mao)
test_core.c          teste do nucleo rodavel em Linux: gcc -fshort-wchar -o test_core test_core.c uc_core.c
```
