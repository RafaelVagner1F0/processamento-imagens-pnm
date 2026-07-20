# Processamento de Imagens PNM

Programa desenvolvido em **C++** para realizar operações de processamento em imagens nos formatos **PNM P2** (tons de cinza) e **PNM P3** (coloridas). O projeto foi desenvolvido como parte do Trabalho Prático 2 da disciplina **INF110 – Programação I**, da **Universidade Federal de Viçosa (UFV)**.

O código-base, contendo as funcionalidades de leitura de imagens, escurecimento e gravação dos arquivos, foi disponibilizado pelo professor **André Gustavo dos Santos**. Todas as demais operações e funcionalidades foram desenvolvidas por mim, **Rafael Vagner Pinto da Fonseca Souza**.

O programa possui uma interface interativa via terminal. Nele, o usuário informa o nome da imagem PNM de entrada, seleciona a operação de processamento desejada e define o nome do arquivo de saída. Após a execução, o resultado é salvo em um novo arquivo no diretório do projeto.

Dessa forma, o programa permite aplicar diferentes filtros e transformações em imagens em tons de cinza e coloridas, gerando um novo arquivo com o resultado do processamento.

---

## Restrições

- O programa suporta apenas imagens nos formatos **PNM P2** (tons de cinza) e **PNM P3** (coloridas).
- Tamanho máximo da imagem: **2000 × 2000 pixels**.

---

## Operações do projeto

- **Escurecimento:** Reduz o brilho da imagem utilizando um fator **k** (1 a 100).
- **Clareamento:** Aumenta o brilho da imagem utilizando um fator **k** (1 a 100).
- **Negativo:** Inverte as cores da imagem.
- **Espelhamento horizontal:** Espelha a imagem em relação ao eixo vertical (esquerda ↔ direita).
- **Espelhamento vertical:** Espelha a imagem em relação ao eixo horizontal (cima ↔ baixo).
- **Filtro de Sobel:** Detecta e realça bordas da imagem.
- **Filtro de Realce (Sharpening):** Destaca detalhes e aumenta a nitidez da imagem.
- **Binarização:** Converte a imagem em apenas duas cores (preto e branco) com base no valor de intensidade de cada pixel.
- **Conversão de imagens coloridas para tons de cinza:** Transforma uma imagem RGB (colorida) em uma imagem em tons de cinza.
---
## Compilação e execução

### Compilar

```bash
g++ tp2code.cpp -o tp2code.exe
```

### Executar

```bash
./tp2code.exe
```

---

## Exemplos de resultados

### Escurecimento

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/escurecimento/antes.jpg) | ![](imagens_jpg/escurecimento/depois.jpeg) |

---

### Clareamento

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/clareamento/antes.jpg) | ![](imagens_jpg/clareamento/depois.jpeg) |

---

### Negativo
#### Exemplo 1
| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/negativo/antes.jpg) | ![](imagens_jpg/negativo/depois.jpeg) |
#### Exemplo 2
| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/negativo/antes2.jpg) | ![](imagens_jpg/negativo/depois2.jpeg) |

---

### Espelhamento Horizontal

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/espelho-horizontal/antes.jpeg) | ![](imagens_jpg/espelho-horizontal/depois.jpeg) |

---

### Espelhamento Vertical

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/espelho-vertical/antes.jpg) | ![](imagens_jpg/espelho-vertical/depois.jpeg) |

---

### Filtro de Sobel
#### Exemplo 1
| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/filtro-sobel/antes.jpg) | ![](imagens_jpg/filtro-sobel/depois.jpeg) |
#### Exemplo 2
| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/filtro-sobel/antes2.jpg) | ![](imagens_jpg/filtro-sobel/depois2.jpeg) |

---

### Filtro de Realce (Sharpening)

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/filtro-realce/antes.jpeg) | ![](imagens_jpg/filtro-realce/depois.jpeg) |

---

### Binarização

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/binarizacao/antes.jpg) | ![](imagens_jpg/binarizacao/depois.jpeg) |

---

### Conversão para Tons de Cinza

| Antes | Depois |
|:------:|:------:|
| ![](imagens_jpg/colorida-tonsdecinza/antes.jpg) | ![](imagens_jpg/colorida-tonsdecinza/depois.jpeg) |
