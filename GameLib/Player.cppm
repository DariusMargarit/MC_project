export module Player;

export import "IPlayer.h";

export class Player : public IPlayer {
public:
	Player();
	Player(char*,const std::string&);
	Player(const Player* other);
	Player(Player&& other) noexcept;
	~Player();
	Player& operator= (const Player* other);
	Player& operator = (Player&& other) noexcept;

	char* GetColor() const override;
	const std::string& GetName() const override;

private:
	char* m_color;
	std::string m_name;

};
