//
// Created by Jason Shen on 5/21/18.
//

#ifndef HIERARCHICAL_MAP_MAP_NETWORK_H
#define HIERARCHICAL_MAP_MAP_NETWORK_H
#include <hierarchical_map_compiler/map_cluster.h>
#include <psdd/psdd_node.h>

class MapNetwork {
 public:
  explicit MapNetwork(std::vector<MapCluster*> clusters, Graph* graph);
  ~MapNetwork() { delete (graph_); }
  static MapNetwork* MapNetworkFromJsonSpecFile(const char* filename);
  static MapNetwork* MapNetworkFromJsonSpec(const json& json_spec);
  MapCluster* root_cluster() const;
  // Returns a map whose value cluster contains the key edge as the internal
  // edge
  std::unordered_map<Edge*, MapCluster*> EdgeClusterMap() const;
  std::pair<PsddNode*, PsddManager*> CompileConstraint() const;
  // Compiler setting
  void SetGraphillionCompiler(std::string graphillion_script,
                              std::string tmp_dir, int thread_num);

 private:
  std::vector<MapCluster*> clusters_;
  Graph* graph_;
  std::unordered_map<MapCluster*, std::set<NodeSize>>
  ConstructEntryPointsForTerminalPath() const;
  std::unordered_map<MapCluster*, std::set<std::pair<NodeSize, NodeSize>>>
  ConstructEntryPointsForNonTerminalPath(
      const std::unordered_map<Edge*, MapCluster*>& edge_cluster_map) const;
  // compiler setting
  std::string graphillion_script_;
  std::string graphillion_tmp_dir_;
  int graphillion_thread_num_;
};

#endif  // HIERARCHICAL_MAP_MAP_NETWORK_H
