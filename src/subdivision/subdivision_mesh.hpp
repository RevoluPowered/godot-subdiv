#pragma once
#include "godot_cpp/classes/global_constants.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/core/binder_common.hpp"

#include "godot_cpp/classes/mesh.hpp"
#include "godot_cpp/classes/mesh_instance3d.hpp"

#include "godot_cpp/templates/hash_map.hpp"
#include "godot_cpp/templates/vector.hpp"

#include "rendering/local_mesh.h"
#include "resources/topology_data_mesh.hpp"

using namespace godot;

//SubdivisionMesh is only for subdividing ImporterQuadMeshes
class SubdivisionMesh : public RefCounted {
	GDCLASS(SubdivisionMesh, RefCounted);

private:
	RID source_mesh; //ImporterQuadMesh
	Ref<LocalMesh> subdiv_mesh; //generated triangle mesh

	int current_level = -1;

protected:
	static void _bind_methods();
	Array _get_subdivided_arrays(const Array &p_arrays, int p_level, int32_t p_format, bool calculate_normals, TopologyDataMesh::TopologyType topology_type);

	Vector<int64_t> subdiv_vertex_count; //variables used for compatibility with mesh
	Vector<int64_t> subdiv_index_count;

public:
	SubdivisionMesh();
	~SubdivisionMesh();

	RID get_rid() const;
	void update_subdivision(Ref<TopologyDataMesh> p_mesh, int p_level);
	void _update_subdivision(Ref<TopologyDataMesh> p_mesh, int p_level, const Vector<Array> &cached_data_arrays);
	void update_subdivision_vertices(int p_surface, const PackedVector3Array &new_vertex_array,
			const PackedInt32Array &index_array, TopologyDataMesh::TopologyType topology_type);
	void clear();

	int64_t surface_get_vertex_array_size(int p_surface) const;
	int64_t surface_get_index_array_size(int p_surface) const;
};