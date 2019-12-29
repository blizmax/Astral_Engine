#include "ResourceAnimation.h"

bool Channel::PosHasKey() const
{
	return !PositionKeys.empty();
}

std::map<double, float3>::iterator Channel::PrevPosition(double current, uint start, uint end)
{
	std::map<double, float3>::iterator ret = PositionKeys.lower_bound(current);
	if (ret != PositionKeys.begin())
		ret--;

	return ret;
}

std::map<double, float3>::iterator Channel::NextPosition(double current, uint start, uint end)
{
	return PositionKeys.upper_bound(current);
}

bool Channel::RotHasKey() const
{
	return !RotationKeys.empty();
}

std::map<double, Quat>::iterator Channel::PrevRotation(double current, uint start, uint end)
{
	std::map<double, Quat>::iterator ret = RotationKeys.lower_bound(current);
	if (ret != RotationKeys.begin())
		ret--;
	return ret;
}

std::map<double, Quat>::iterator Channel::NextRotation(double current, uint start, uint end)
{
	return RotationKeys.upper_bound(current);
}

bool Channel::ScaleHasKey() const
{
	return !ScaleKeys.empty();
}

std::map<double, float3>::iterator Channel::PrevScale(double current, uint start, uint end)
{
	std::map<double, float3>::iterator ret = ScaleKeys.lower_bound(current);
	if (ret != ScaleKeys.begin())
		ret--;
	return ret;
}

std::map<double, float3>::iterator Channel::NextScale(double current, uint start, uint end)
{
	return ScaleKeys.upper_bound(current);
}