classDiagram
    class Character {
        -string name
        -int hp
        -int defense
        -int attack
        -int magic
        -vector equipment
        -vector ascii
        -bool raisedDefenses
        +Character(name)
        +Character(name, baseDefense, baseAttack, baseMagic, equipment);
        +Character(name, defense, attack, magic, equipment, ascii);
        +getName() string
        +getHp() int
        +setHp(value)
        +getDefense() int
        +getAttack() int
        +getMagic() int
        +printAscii()
        +dealDamage(target)
        +takeDamage(rawDamage)
        +cure()
        +defend(havePlayerDefended) bool
        +action(choice, target, havePlayerDefended) int
    }
    class Enemy {
        +Enemy()
        +Enemy(name)
        +Enemy(name, defense, attack, magic)
        +autoAction(target, haveEnemyDefended) int
    }
    class Item {
        -string name
        -string quest
        -string description
        -ItemType type
        -vector ascii
        -int bonus
        +Item(name, quest, description, type, ascii, bonus)
        +getName() string
        +getDescription() string
        +getQuest() string
        +getType() ItemType
        +getAscii() vector
        +getBonus() int
    }
    class ItemRegistry {
        -map itemMap
        -vector unlockedItems
        -string itemsFilePath
        +ItemRegistry(itemsFilePath)
        +loadItemsFromFile()
        +getItem(id) Item
        +getNumItems() int
        +getUnlockedItems() vector
        +addItem(item)
        +unlockItem(id)
        +lockItem(id)
        +isUnlocked(id) bool
        +getIdByName(name) int
    }
    class Battle {
        -bool battleOver
        -int whoWon
        -bool havePlayerDefended
        -bool haveEnemyDefended
        -int playerAction
        -int enemyAction
        +Character player
        +Enemy enemy
        +Battle(player, enemy)
        +playerTurn()
        +enemyTurn()
        +checkBattleStatus()
        +setBattleOver()
        +getPlayer() Character
        +getEnemy() Character
    }
    class Save {
        -Character hero
        -int currentEnemyIndex
        -bool isWritten
        +Save()
        +getHero() Character
        +getCurrentEnemyIndex() int
        +getIsWritten() bool
        +saveToFile(hero, registry, saveIndex) bool
        +saveToVector(hero, enemyIndex) bool
        +deleteSave() bool
    }
    class Game {
        +GameState currentState
        +size_t selectedOption
        +Character player
        +bool isBattleActive
        +bool isBattleOver
        +int selectedHorizontal
        +int currentEnemyIndex
        +indexedSave currentSave
        +getEnemyByIndex(index) Enemy
        +getTotalEnemies() size_t
        +handleInput()
        +render()
    }
    Enemy --|> Character
    Battle --> "1" Character : Tem
    Battle --> "1" Enemy : Tem
    Save --> "1" Character : Tem
    Save --> "1" ItemRegistry : Usa
    Character --> "0..*" Item : Equipa
    ItemRegistry --> "0..*" Item : Gerencia
    Game --> "1" Character : Tem
    Game --> "0..1" Battle : Tem Ativo
    Game --> "0..*" Save : Tem
    Save --> "*..*" Item : Tem
