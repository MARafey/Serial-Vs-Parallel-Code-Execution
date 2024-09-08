#include <iostream>
#include <vector>
#include <algorithm>

struct Activity
{
    int start;
    int end;
};

bool compare(Activity a, Activity b)
{
    return a.end < b.end;
}

void selectActivities(std::vector<Activity> &activities)
{
    std::sort(activities.begin(), activities.end(), compare);

    int n = activities.size();
    std::cout << "Selected activities:\n";
    int lastEndTime = -1;

    for (int i = 0; i < n; ++i)
    {
        if (activities[i].start > lastEndTime)
        {
            std::cout << "Activity (" << activities[i].start << ", " << activities[i].end << ")\n";
            lastEndTime = activities[i].end;
        }
    }
}

int main()
{
    std::vector<Activity> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}, {1, 3}, {3, 8}, {6, 8}, {7, 10}, {9, 11}, {10, 12}};

    selectActivities(activities);

    return 0;
}
