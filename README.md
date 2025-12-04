# Sistema-Solar
Sistema Solar desenvolvida em C++ com a biblioteca OpenGL (GLUT) dentro da disciplina de Computação Gráfica. Possui movimentação de câmera e aceleração/desaceleração do sistema via teclado.

## 🚀 Funcionalidades

* **Simulação Completa:** Representação do Sol e dos planetas (Mercúrio, Vênus, Terra + Lua, Marte, Júpiter, Saturno + Anéis, Urano e Netuno) com textura.
* **Animação em Tempo Real:** Movimentos de translação (órbita) e rotação simulados automaticamente.
* **Sistema de Câmeras:** Eixo Y e Eixo Z podendo ser alterado via teclado, causando uma perspectiva de zoom dentro do sistema.
* **Aceleração:** Movimentos de rotação e translação dos planetas podendo ser alterado via teclado.


## 🎮 Teclas de Atalho

Interaja com a simulação utilizando o teclado:

| Tecla | Ação |
| :---: | :--- |
| **+** | Acelera a velocidade de translação e rotação em 10% |
| **-** | Desacelera a velocidade de translação e rotação em 10% |
| **W** | Aumenta em 5 unidades no Eixo Y (sobe a câmera) |
| **S** | Diminui em 5 unidades no Eixo Y (desce a câmera) |
| **A** | Aumenta em 5 unidades no Eixo Z (afasta a câmera) |
| **D** | Diminui em 5 unidades no Eixo Z (aproxima a câmera) |
| **ESPAÇO** | Pausa/Despausa o sistema solar |
| **0** | Retorna para a câmera e velocidade padrão|
| **ESC** | Fecha a aplicação |

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++
* **Biblioteca Gráfica:** OpenGL
* **Utility Toolkit:** GLUT (OpenGL Utility Toolkit)
