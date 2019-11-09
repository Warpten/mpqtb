#pragma once

#include <memory>
#include <array>

#include "m2_types.hpp"

namespace fs {
    class m2 : public std::enable_shared_from_this<m2> {
    public:
        m2(const uint8_t* fileData);

        template <typename T>
        T* read() {
            T* data = reinterpret_cast<T*>(_fileData + _cursor);
            _cursor += sizeof(T);
            return data;
        }

        template <typename T, size_t N>
        std::array<T, N> read() {
            std::array<T, N> arr;
            memcpy(arr.data(), _fileData + _cursor, sizeof(T) * N);
            return arr;
        }

        void* base() {
            return (void*) _fileData;
        }

        struct header_t {
            uint32_t magic;
            uint32_t version;
            M2Array<char> name;
            struct {
                uint32_t flag_tilt_x : 1;
                uint32_t flag_tilt_y : 1;
                uint32_t : 1;
                uint32_t flag_use_texture_combiner_combos : 1;   // add textureCombinerCombos array to end of data
                uint32_t : 1;
                uint32_t flag_load_phys_data : 1;
                uint32_t : 1;
                uint32_t flag_unk_0x80 : 1;                      // with this flag unset, demon hunter tattoos stop glowing
                uint32_t flag_camera_related : 1;                // TODO: verify version
            } global_flags;
            M2Array<M2Loop> global_loops;                        // Timestamps used in global looping animations.
            M2Array<M2Sequence> sequences;                       // Information about the animations in the model.
            M2Array<uint16_t> sequenceIdxHashById;               // Mapping of sequence IDs to the entries in the Animation sequences block.
            M2Array<M2CompBone> bones;                           // MAX_BONES = 0x100 => Creature\SlimeGiant\GiantSlime.M2 has 312 bones (Wrath)
            M2Array<uint16_t> boneIndicesById;                   // Lookup table for key skeletal bones. (alt. name: key_bone_lookup)
            M2Array<M2Vertex> vertices;
            uint32_t num_skin_profiles;                          // Views (LOD) are now in .skins.
            M2Array<M2Color> colors;                             // Color and alpha animations definitions.
            M2Array<M2Texture> textures;
            M2Array<M2TextureWeight> texture_weights;            // Transparency of textures.
            M2Array<M2TextureTransform> texture_transforms;
            M2Array<uint16_t> textureIndicesById;                // (alt. name: replacable_texture_lookup)
            M2Array<M2Material> materials;                       // Blending modes / render flags.
            M2Array<uint16_t> boneCombos;                        // (alt. name: bone_lookup_table)
            M2Array<uint16_t> textureCombos;                     // (alt. name: texture_lookup_table)
            M2Array<uint16_t> textureTransformBoneMap;           // (alt. name: tex_unit_lookup_table)
            M2Array<uint16_t> textureWeightCombos;               // (alt. name: transparency_lookup_table)
            M2Array<uint16_t> textureTransformCombos;            // (alt. name: texture_transforms_lookup_table)
            CAaBox bounding_box;                                 // min/max( [1].z, 2.0277779f ) - 0.16f seems to be the maximum camera height
            float bounding_sphere_radius;                        // detail doodad draw dist = clamp (bounding_sphere_radius * detailDoodadDensityFade * detailDoodadDist, …)
            CAaBox collision_box;
            float collision_sphere_radius;
            M2Array<uint16_t> collisionIndices;                  // (alt. name: collision_triangles)
            M2Array<C3Vector> collisionPositions;                // (alt. name: collision_vertices)
            M2Array<C3Vector> collisionFaceNormals;              // (alt. name: collision_normals) 
            M2Array<M2Attachment> attachments;                   // position of equipped weapons or effects
            M2Array<uint16_t> attachmentIndicesById;             // (alt. name: attachment_lookup_table)
            M2Array<M2Event> events;                             // Used for playing sounds when dying and a lot else.
            M2Array<M2Light> lights;                             // Lights are mainly used in loginscreens but in wands and some doodads too.
            M2Array<M2Camera> cameras;                           // The cameras are present in most models for having a model in the character tab. 
            M2Array<uint16_t> cameraIndicesById;                 // (alt. name: camera_lookup_table)
            M2Array<M2Ribbon> ribbon_emitters;                   // Things swirling around. See the CoT-entrance for light-trails.
            /*M2Array<M2Particle> particle_emitters;

#if >= BC                                                       // TODO: verify version
            if (flag_use_texture_combiner_combos)
            {
                M2Array<uint16_t> textureCombinerCombos;           // When set, textures blending is overriden by the associated array.
            }
#endif*/
        };

        header_t const& header() const {
            return _header;
        }
    private:
        header_t _header;
        const uint8_t* _fileData;
        size_t _cursor;
    };
}