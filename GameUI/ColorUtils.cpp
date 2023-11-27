#include "ColorUtils.h"

void ColorUtils::GenerateColorVector(std::vector<EColor>& colors)
{
	const int begin = static_cast<int>(EColor::Red);
	const int end = static_cast<int>(EColor::NoColor);

	for (int index = begin; index < end; index++)
	{
		EColor currentColor = static_cast<EColor>(index);
		colors.push_back(std::move(currentColor));
	}
}

QString ColorUtils::TwixtColorToString(EColor color)
{
	switch (color)
	{
	case EColor::Red:
		return std::move(QString("Red"));
	case EColor::Blue:
		return std::move(QString("Blue"));
	case EColor::Pink:
		return std::move(QString("Pink"));
	case EColor::Purple:
		return std::move(QString("Purple"));
	case EColor::Yellow:
		return std::move(QString("Yellow"));
	case EColor::Orange:
		return std::move(QString("Orange"));
	default:
		return std::move(QString(""));
	}
}

EColor ColorUtils::StringToTwixtColor(QString string)
{
	static const std::vector<QString> colors{ "Red", "Blue", "Pink", "Purple", "Yellow", "Orange" };

	for (int index = 0; index < colors.size(); index++)
	{
		if (string.compare(colors[index]) == 0)
			return std::move(static_cast<EColor>(index));
	}

	return std::move(EColor::NoColor);
}

const QColor ColorUtils::TwixtColorToQColor(EColor color)
{
	switch (color)
	{
	case EColor::Red:
		return std::move(QColor("#E2001B"));
	case EColor::Blue:
		return std::move(QColor("#4798CE"));
	case EColor::Pink:
		return std::move(QColor("#de27e8"));
	case EColor::Purple:
		return std::move(QColor("#9e67f0"));
	case EColor::Yellow:
		return std::move(QColor("#c9b465"));
	case EColor::Orange:
		return std::move(QColor("#d97f30"));
	default:
		return Qt::transparent;

	}
}