#include "skip_list.cpp"
#include <iostream>

int main() {
  skip_list sl;

  std::cout << "Inserting values..." << std::endl;
  sl.insert_node(10, 10);
  sl.insert_node(20, 20);
  sl.insert_node(30, 30);

  std::cout << "Searching for values..." << std::endl;
  int keys[] = {10, 20, 30, 40};
  for (int key : keys) {
    skip_node *node = sl.get_data(key);
    if (node) {
      std::cout << "Found " << node->data << std::endl;
    } else {
      std::cout << "Value " << key << " not found." << std::endl;
    }
  }

  std::cout << "Deleting value 20 and attempting to retrieve it again..."
            << std::endl;
  sl.delete_node(20);
  if (sl.get_data(20)) {
    std::cout << "Value 20 found (error)." << std::endl;
  } else {
    std::cout << "Value 20 not found (expected)." << std::endl;
  }

  return 0;
}
