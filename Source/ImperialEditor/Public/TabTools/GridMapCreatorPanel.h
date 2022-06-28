#pragma once

class GridMapCreatorPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(GridMapCreatorPanel)
	{}
	SLATE_ARGUMENT(TWeakPtr<class GridMapCreator>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

protected:
	TWeakPtr<GridMapCreator> GridMapCreator;
};

