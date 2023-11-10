export module Player;

export import "IPlayer.h";

export class Player : public IPlayer
{
public:
	Player(std::string_view name, std::string_view color);
	Player(const Player* other);
	Player(Player&& other) noexcept;
	Player& operator= (const Player* other);
	Player& operator= (Player&& other) noexcept;

	std::string_view GetColor() const override;
	std::string_view GetName() const override;

private:
	std::string m_name, m_color;
};
