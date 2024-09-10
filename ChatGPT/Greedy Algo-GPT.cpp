#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

struct Activity
{
    int start;
    int end;
};

// Comparator for sorting activities by their end time
bool compare(Activity a, Activity b)
{
    return a.end < b.end;
}

void selectActivities(std::vector<Activity> &activities)
{
    // Parallelizing the sorting using OpenMP
    #pragma omp parallel
    {
        #pragma omp single
        std::sort(activities.begin(), activities.end(), compare);
    }

    int n = activities.size();
    std::vector<Activity> selectedActivities;
    int lastEndTime = -1;

    // Selecting activities in parallel, but ensuring thread safety with critical sections
    #pragma omp parallel for
    for (int i = 0; i < n; ++i)
    {
        if (activities[i].start > lastEndTime)
        {
            #pragma omp critical
            {
                if (activities[i].start > lastEndTime)
                {
                    selectedActivities.push_back(activities[i]);
                    lastEndTime = activities[i].end;
                }
            }
        }
    }

    // Displaying selected activities (can be done in a single-threaded context)
    std::cout << "Selected activities:\n";
    for (auto &activity : selectedActivities)
    {
        std::cout << "Activity (" << activity.start << ", " << activity.end << ")\n";
    }
}

int main()
{
    std::vector<Activity> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {8, 9}, {5, 9}, {1, 3}, {3, 8}, {6, 8}, {7, 10}, {9, 11}, {10, 12}};

    selectActivities(activities);

    return 0;
}
