#pragma once
class IGame {
	virtual void PlaceColumn(IPosition position) = 0;
	virtual void MakeBridge(IPosition firstPosition, IPosition secondPosition) = 0;
	virtual void RemoveBridge(IPosition firstPosition, IPosition secondPosition) = 0;
};