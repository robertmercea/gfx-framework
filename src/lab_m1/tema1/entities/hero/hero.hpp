
namespace tema1 {
namespace entities {

class Hero {
public:
  void heal(int amount);
  void damage(int amount);
  void render();
private:
  int health;
  int attack;
};

} // namespace entities
} // namespace tema1

