#include "Precomplied.h"
#include "PerceptionModule.h"

using namespace AI;

PerceptionModule::PerceptionModule(Agent& agent, ImportanceCalculator calculator)
	:mAgent(agent)
	,ComputeImportance(calculator)
{

}

void PerceptionModule::Update(float deltaTime)
{
	for (auto& sensor : mSensors)
	{
		sensor->Update(mAgent, mMemoryRecords, deltaTime);
	}

	mMemoryRecords.erase(
		std::remove_if(
			mMemoryRecords.begin(),
			mMemoryRecords.end(),
			[span = mMemorySpan](const auto& record)
			{
				return record.lastRecordedTime + span < X::GetTime();
			}), mMemoryRecords.end());

	for (auto& record : mMemoryRecords)
	{
		record.importance = ComputeImportance(mAgent, record);
	}

	mMemoryRecords.sort(
		[](const auto& a, const auto& b)
		{
			return a.importance > b.importance;
		});
}