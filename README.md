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

Requer apenas Python 3 e o binutils/GCC (o mesmo fluxo ja usado antes; nada de
mingw-w64 nem CRT — o exe importa direto de msvcrt/kernel32/user32/gdi32/comdlg32/shell32):

```
python3 build.py
```

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
