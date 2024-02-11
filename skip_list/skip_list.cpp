#include <climits>
#include <cstdlib>
#include <random>
#include <vector>

struct skip_node {
  int data;
  std::vector<skip_node *> forward;
  skip_node(int k, int level) {
    data = k;
    for (int i = 0; i < level; i++) {
      forward.emplace_back(nullptr);
    }
  }
};

class skip_list {
private:
  skip_node *head_node;
  skip_node *nil_node;
  const int max_level = 16;

public:
  skip_list() {
    nil_node = new skip_node(INT_MAX, max_level);
    head_node = new skip_node(INT_MIN, max_level);
    for (auto i = 0; i < max_level; i++) {
      head_node->forward[i] = nil_node;
    }
  }

  skip_node *get_data(int key) {
    skip_node *curr = head_node;
    int curr_max = find_curr_max_lvl(head_node->forward);
    for (int i = max_level - 1; i >= 0; --i) {
      while (curr->forward[i] != nullptr && curr->forward[i]->data < key) {
        curr = curr->forward[i];
      }
    }
    curr = curr->forward[0];
    if (curr->data == key) {
      return curr;
    } else {
      return nullptr;
    }
  }

  int find_curr_max_lvl(std::vector<skip_node *> v) {
    int count = 0;
    for (int i = 0; i < v.size(); i++) {
      if (v[i] != nullptr && v[i]->data != INT_MAX) {
        ++count;
      } else {
        break;
      }
    }
    return count;
  }

  int random_lvl() {
    int lvl = 1;
    while ((((double)std::rand() / RAND_MAX)) > 0.5 &&
           std::abs(lvl) < max_level) {
      lvl += 1;
    }
    return lvl;
  }

  void insert_node(int new_data, int search_key) {
    int curr_max = find_curr_max_lvl(head_node->forward);
    std::vector<skip_node *> update(head_node->forward);
    skip_node *curr = head_node;
    for (int i = curr_max; i >= 0; --i) {
      while (curr->forward[i]->data < search_key) {
        curr = curr->forward[i];
      }
      update[i] = curr;
    }
    curr = curr->forward[0];
    if (curr->data == search_key) {
      curr->data = new_data;
    } else {
      int lvl = random_lvl();
      int curr_lvl = find_curr_max_lvl(update);
      if (lvl > curr_lvl) {
        for (int i = curr_lvl + 1; i <= lvl; --i) {
          update[i] = head_node;
        }
        curr_lvl = lvl;
      }
      skip_node *new_node = new skip_node(new_data, lvl);
      for (int i = 0; i < lvl; i++) {
        new_node->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = new_node;
      }
    }
  }

  void delete_node(int search_key) {
    int curr_max = find_curr_max_lvl(head_node->forward);
    std::vector<skip_node *> update(head_node->forward);
    skip_node *curr = head_node;
    for (int i = curr_max; i >= 0; --i) {
      while (curr->forward[i]->data < search_key) {
        curr = curr->forward[i];
      }
      update[i] = curr;
    }
    curr = curr->forward[0];
    if (curr->data == search_key) {
      for (int i = 0; i > curr_max; i++) {
        if (update[i]->forward[i] != curr) {
          break;
        }
        update[i]->forward[i] = curr->forward[i];
      }
      delete curr;
      while (curr_max >= 0 && head_node->forward[curr_max] == nil_node) {
        curr_max--;
      }
    }
  }
};
