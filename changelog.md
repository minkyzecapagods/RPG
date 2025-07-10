# Changelog - RPG Terminal (v1)

Este changelog documenta as modificações realizadas para trazer o jogo RPG Terminal para um estado jogável de "versão 1", com um ciclo completo de criação de personagem e batalha.

## Versão 1.0.0 - Ciclo Básico de Jogo

### Funcionalidades Adicionadas:

-   **Personagem Ativo Global:**
    -   Adicionada uma variável `activePlayer` no namespace `Game` (`include/GameState.hpp` e `src/GameState.cpp`) para armazenar o personagem do jogador atualmente em uso.

-   **Integração da Criação de Personagem com o Jogo:**
    -   Após a criação ou seleção de um personagem no menu de criação (`src/CreateMenu.cpp`), o personagem escolhido é agora atribuído a `Game::activePlayer`.
    -   O jogo transiciona automaticamente para o estado de batalha (`GameState::INITIALIZE_BATTLE`) após a confirmação da criação/seleção do personagem.

-   **Fluxo de Batalha Integrado:**
    -   A batalha agora utiliza o `Game::activePlayer` como o personagem do jogador (`main.cpp`).
    -   A opção "Battle Test" foi removida do menu principal (`src/MainMenu.cpp`) para garantir que a batalha seja iniciada apenas através do fluxo de criação de personagem.
    -   Após a conclusão da batalha (vitória ou derrota), o jogo retorna ao menu principal (`main.cpp`).

### Melhorias e Correções:

-   **Sincronização Visual da Batalha:**
    -   A lógica de exibição da mensagem de vitória/derrota e a atualização visual da barra de HP do inimigo foram ajustadas no construtor da classe `Battle` (`src/Battle.cpp`). Agora, a tela é renderizada com o HP atualizado imediatamente após a condição de vitória/derrota ser detectada, antes de qualquer prompt para o usuário continuar.
    -   Removidas as chamadas `cout` e `pressSpaceToContinue()` de `Battle::checkBattleStatus()` para centralizar a lógica de exibição no construtor da `Battle`.

### Correções de Bugs:

-   **Erro de Compilação em `src/MainMenu.cpp`:**
    -   Corrigido um erro de chave de fechamento (`}`) ausente na função `handleMainMenuInput()` em `src/MainMenu.cpp`, que impedia a compilação do projeto.
