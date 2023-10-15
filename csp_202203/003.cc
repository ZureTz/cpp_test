#include <algorithm>
#include <climits>
#include <iostream>
#include <list>
using namespace std;

struct block;
struct task {
  int application_number;
  int is_allocated_at; // numeral index from 1; 0 represents not allocated
  block *motherBlock;
  task(int app, block *s_Block = nullptr)
      : application_number(app), is_allocated_at(0), motherBlock(s_Block) {}
};

struct area;
struct block {
  list<task *> subTasks;
  int index;
  area *motherArea;
  block(area *s_Area = nullptr) : motherArea(s_Area) {}
};

struct area {
  list<block *> subBlocks;
  int index;
};

int main(int argc, char const *argv[]) {
  int n_areas, n_blocks;
  cin >> n_blocks >> n_areas;

  auto areas = new area[n_areas];
  for (int i = 0; i < n_areas; i++) {
    areas[i].index = i + 1;
  }

  auto blocks = new block[n_blocks];
  for (int i = 0; i < n_blocks; i++) {
    int block_index;
    cin >> block_index;
    areas[block_index - 1].subBlocks.push_back(blocks + i);
    blocks[i].motherArea = areas + block_index - 1;
    blocks[i].index = i + 1;
  }

  int n_task_groups;
  cin >> n_task_groups;
  list<task *> tasks;
  for (int i = 0; i < n_task_groups; i++) {
    int n_tasks, application_number;
    int area_requirement(0), task_requirement(0), rev_task_requirement(0);
    bool restrict_rev_task_requirement(false);
    cin >> n_tasks >> application_number;
    cin >> area_requirement >> task_requirement >> rev_task_requirement;
    cin >> restrict_rev_task_requirement;

    auto tasksSizeComp = [](const block &a, const block &b) {
      return a.subTasks.size() < b.subTasks.size();
    };

    if (area_requirement == 0) {
      for (int j = 0; j < n_tasks; j++) {
        int min = min_element(blocks, blocks + n_blocks, tasksSizeComp)
                      ->subTasks.size();

        bool is_allocated = false;
        for (int k = 0; k < n_blocks; k++) {
          if (blocks[k].subTasks.size() != min) {
            continue;
          }
          tasks.push_back(new task(application_number, blocks + k));
          tasks.back()->is_allocated_at = k;
          blocks[k].subTasks.push_back(tasks.back());
          is_allocated = true;
          break;
        }
        if (!is_allocated) {
          tasks.push_back(new task(application_number));
        }
        continue;
      }
    }

    list<block *> temp_blocks;
    for (int k = 0; k < n_blocks; k++) {
      if (blocks[k].motherArea->index != area_requirement) {
        continue;
      }
      temp_blocks.push_back(blocks + k);
    }

    
    int min = (*min_element(temp_blocks.begin(), temp_blocks.end(),
                            [](block *a, block *b) {
                              return a->subTasks.size() < b->subTasks.size();
                            }))
                  ->subTasks.size();

    bool is_allocated = false;
    for (int k = 0; k < n_blocks; k++) {
      if (blocks[k].subTasks.size() != min) {
        continue;
      }
      tasks.push_back(new task(application_number, blocks + k));
      tasks.back()->is_allocated_at = k + 1;
      blocks[k].subTasks.push_back(tasks.back());
      is_allocated = true;
      cout << tasks.back()->is_allocated_at << " ";
      break;
    }
    if (!is_allocated) {
      tasks.push_back(new task(application_number));
      cout << tasks.back()->is_allocated_at << " ";
    }
    continue;
  }

  delete[] areas;
  delete[] blocks;
  return 0;
}