#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

struct Activity
{
    int start;
    int end;
};

bool compare(Activity a, Activity b)
{
    return a.end < b.end;
}

void selectActivitiesParallel(std::vector<Activity> &activities)
{
    std::sort(activities.begin(), activities.end(), compare);

    int n = activities.size();
    std::cout << "Selected activities:\n";

    #pragma omp parallel for shared(activities)
    for (int i = 0; i < n; ++i)
    {
        if (i == 0 || activities[i].start >= activities[i - 1].end)
        {
            #pragma omp critical
            {
                std::cout << "Activity (" << activities[i].start << ", " << activities[i].end << ")\n";
            }
        }
    }
}

int main()
{
    std::vector<Activity> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}, {1, 3}, {3, 8}, {6, 8}, {7, 10}, {9, 11}, {10, 12}};

    selectActivitiesParallel(activities);

    return 0;
}