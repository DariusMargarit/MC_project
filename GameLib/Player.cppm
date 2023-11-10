export module Player;

export import "IPlayer.h";

export class Player : public IPlayer {
public:
	char* GetColor() const override;
	const std::string& GetName() const override;

private:
	char* m_color;
	std::string m_name;

};
