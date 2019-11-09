#pragma once

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace fs {
    class m2;

    template<typename T>
    struct M2Array {
        uint32_t count;
        uint32_t offset; // pointer to T, relative to begin of m2 data block (i.e. MD21 chunk content or begin of file)

        inline T* read(m2 const& model, size_t index) const {
            if (index >= count)
                throw std::runtime_error("index too large");

            return reinterpret_cast<T*>(reinterpret_cast<uint8_t*>(model.base()) + offset + sizeof(T) * index);
        }

        inline std::vector<T> operator >> (m2 const& model) {
            std::vector<T> v(count);
            memcpy(v.data(), model.base() + offset, model.base() + offset + count * sizeof(T));
            return v;
        }
    };

    template<typename T>
    struct M2SplineKey {
        T value;
        T inTan;
        T outTan;
    };

    struct M2Loop {
        uint32_t timestamp;
    };

    struct M2Range {
        uint32_t minimum;
        uint32_t maximum;
    };

    struct M2TrackBase {
        uint16_t interpolation_type;
        uint16_t global_sequence;
        M2Array<M2Array<uint32_t>> timestamps;
    };

    template<typename T>
    struct M2Track : public M2TrackBase {
        M2Array<M2Array<T>> values;
    };

    struct C2Vector {
        float x;
        float y;
    };

    struct C3Vector {
        float x;
        float y;
        float z;
    };

    struct C4Quaternion {
        float x;
        float y;
        float z;
        float w; // Unlike Quaternions elsewhere, the scalar part ('w') is the last element in the struct instead of the first
    };

    struct M2CompQuat {
        uint16_t x, y, z, w;
    };

    struct CAaBox {
        C3Vector min;
        C3Vector max;
    };

    struct CAaSphere {
        C3Vector position;
        float radius;
    };

    struct M2Bounds {
        CAaBox extent;
        float radius;
    };

    struct M2CompBone {
        int32_t key_bone_id;            // Back-reference to the key bone lookup table. -1 if this is no key bone.
        enum {
            spherical_billboard = 0x8,
            cylindrical_billboard_lock_x = 0x10,
            cylindrical_billboard_lock_y = 0x20,
            cylindrical_billboard_lock_z = 0x40,
            transformed = 0x200,
            kinematic_bone = 0x400,       // MoP+: allow physics to influence this bone
            helmet_anim_scaled = 0x1000,  // set blend_modificator to helmetAnimScalingRec.m_amount for this bone
        };
        uint32_t flags;
        int16_t parent_bone;            // Parent bone ID or -1 if there is none.
        uint16_t submesh_id;            // Mesh part ID OR uDistToParent?
        union {                         // only ? BC?
            struct {
                uint16_t uDistToFurthDesc;
                uint16_t uZRatioOfChain;
            } CompressData;               // No model has ever had this part of the union used.
            uint32_t boneNameCRC;         // these are for debugging only. their bone names match those in key bone lookup.
        };
        M2Track<C3Vector> translation;
        M2Track<M2CompQuat> rotation;   // compressed values, default is (32767,32767,32767,65535) == (0,0,0,1) == identity
        M2Track<C3Vector> scale;
        C3Vector pivot;                 // The pivot point of that bone.
    };

    struct M2Sequence {
        uint16_t id;                   // Animation id in AnimationData.dbc
        uint16_t variationIndex;       // Sub-animation id: Which number in a row of animations this one is.
        uint32_t duration;             // The length of this animation sequence in milliseconds.
        float movespeed;               // This is the speed the character moves with in this animation.
        uint32_t flags;                // See below.
        int16_t frequency;             // This is used to determine how often the animation is played. For all animations of the same type, this adds up to 0x7FFF (32767).
        uint16_t _padding;
        M2Range replay;                // May both be 0 to not repeat. Client will pick a random number of repetitions within bounds if given.
        uint32_t blendTime;
        M2Bounds bounds;
        int16_t variationNext;         // id of the following animation of this AnimationID, points to an Index or is -1 if none.
        uint16_t aliasNext;            // id in the list of animations. Used to find actual animation if this sequence is an alias (flags & 0x40)
    };

    struct M2Vertex {
        C3Vector pos;
        uint8_t bone_weights[4];
        uint8_t bone_indices[4];
        C3Vector normal;
        C2Vector tex_coords[2];  // two textures, depending on shader used
    };

    template<typename Base, size_t integer_bits, size_t decimal_bits>
    struct fixed_point
    {
        static const float constexpr factor = integer_bits
            ? (1 << decimal_bits)
            : (1 << (decimal_bits + 1)) - 1;

        union {
            struct {
                Base integer_and_decimal : integer_bits + decimal_bits;
                Base sign : 1;
            };
            Base raw;
        };

        constexpr operator float() const {
            return (sign ? -1.f : 1.f) * integer_and_decimal / factor;
        }
        constexpr fixed_point(float x)
            : sign(x < 0.f), integer_and_decimal(std::abs(x)* factor)
        { }
    };

    using fixed16 = fixed_point<uint16_t, 0, 15>;

    struct M2Color {
        M2Track<C3Vector> color; // vertex colors in rgb order
        M2Track<fixed16> alpha; // 0 - transparent, 0x7FFF - opaque. Normaly NonInterp
    };

    struct M2Texture {
        uint32_t type;          // see below
        uint32_t flags;         // see below
        M2Array<char> filename; // for non-hardcoded textures (type != 0), this still points to a zero-sized string
    };

    struct M2TextureWeight {
        M2Track<fixed16> weight;
    };

    struct M2TextureTransform {
        M2Track<C3Vector> translation;
        M2Track<C4Quaternion> rotation;    // rotation center is texture center (0.5, 0.5)
        M2Track<C3Vector> scaling;
    };

    struct M2Material {
        uint16_t flags;
        uint16_t blending_mode; // apparently a bitfield

        enum {
            unlit = 0x01,
            unfogged = 0x02,
            two_sided = 0x04,
            depth_test = 0x08,
            depth_write = 0x10,
        };
    };

    struct M2Attachment {
        uint32_t id;                        // Referenced in the lookup-block below.
        uint16_t bone;                      // attachment base
        uint16_t unknown;                   // see BogBeast.m2 in vanilla for a model having values here
        C3Vector position;                  // relative to bone; Often this value is the same as bone's pivot point 
        M2Track<uint8_t> animate_attached;  // whether or not the attached model is animated when this model is. only a bool is used. default is true.

        enum {
            shield = 0,
            hand_right = 1,
            hand_left = 2,
            elbow_right = 3,
            elbow_left = 4,
            shoulder_right = 5,
            shoulder_left = 6,
            knee_right = 7,
            knee_left = 8,
            hip_right = 9,
            hip_left = 10,
            helm = 11,
            back = 12,
            shoulder_flap_right = 13,
            shoulder_flap_left = 14,
            chest_blood_front = 15,
            chest_blood_back = 16,
            breath = 17,
            player_name = 18,
            base = 19,
            head = 20,
            spell_left_hand = 21,
            spell_right_hand = 22,
            special_1 = 23,
            special_2 = 24,
            special_3 = 25,
            sheath_main_hand = 26,
            sheath_off_hand = 27,
            sheath_shield = 28,
            player_name_mounted = 29,
            large_weapon_left = 30,
            large_weapon_right = 31,
            hip_weapon_left = 32,
            hip_weapon_right = 33,
            chest = 34,
            hand_arrow = 35,
            bullet = 36,
            spell_hand_omni = 37,
            spell_hand_directed = 38,
            vehicle_seat_1 = 39,
            vehicle_seat_2 = 40,
            vehicle_seat_3 = 41,
            vehicle_seat_4 = 42,
            vehicle_seat_5 = 43,
            vehicle_seat_6 = 44,
            vehicle_seat_7 = 45,
            vehicle_seat_8 = 46,
            left_foot = 47,
            right_foot = 48,
            shield_no_glove = 49,
            spine_low = 50,
            altered_shoulder_r = 51,
            altered_shoulder_l = 52,
            belt_buckle = 53,
            sheath_crossbow = 54,
            head_top = 55
        };
    };

    struct M2Event {
        uint32_t identifier;  // mostly a 3 character name prefixed with '$'.
        uint32_t data;        // This data is passed when the event is fired. 
        uint32_t bone;        // Somewhere it has to be attached.
        C3Vector position;    // Relative to that bone of course, animated. Pivot without animating.
        M2TrackBase enabled;  // This is a timestamp-only animation block. It is built up the same as a normal AnimationBlocks, but is missing values, as every timestamp is an implicit "fire now".
    };

    struct M2Camera {
        uint32_t type;                                  // 0: portrait, 1: characterinfo; -1: else (flyby etc.); referenced backwards in the lookup table.
        float far_clip;
        float near_clip;
        M2Track<M2SplineKey<C3Vector>> positions;       // How the camera's position moves. Should be 3*3 floats.
        C3Vector position_base;
        M2Track<M2SplineKey<C3Vector>> target_position; // How the target moves. Should be 3*3 floats.
        C3Vector target_position_base;
        M2Track<M2SplineKey<float>> roll;              // The camera can have some roll-effect. Its 0 to 2*Pi. 
        M2Track<M2SplineKey<float>> FoV;               // Diagonal FOV in radians. See below for conversion.
    };

    struct M2Light {
        enum light_type : uint16_t {
            directional = 0,
            point_light = 1
        };

        light_type type;
        int16_t bone;                      // -1 if not attached to a bone
        C3Vector position;                 // relative to bone, if given
        M2Track<C3Vector> ambient_color;
        M2Track<float> ambient_intensity;  // defaults to 1.0
        M2Track<C3Vector> diffuse_color;
        M2Track<float> diffuse_intensity;  // defaults to 1.0
        M2Track<float> attenuation_start;
        M2Track<float> attenuation_end;
        M2Track<uint8_t> visibility;       // enabled?

    };

    struct M2Ribbon {
        uint32_t ribbonId;                  // Always (as I have seen): -1.
        uint32_t boneIndex;                 // A bone to attach to.
        C3Vector position;                  // And a position, relative to that bone.
        M2Array<uint16_t> textureIndices;   // into textures
        M2Array<uint16_t> materialIndices;  // into materials
        M2Track<C3Vector> colorTrack;
        M2Track<fixed16> alphaTrack;        // And an alpha value in a short, where: 0 - transparent, 0x7FFF - opaque.
        M2Track<float> heightAboveTrack;
        M2Track<float> heightBelowTrack;    // do not set to same!
        float edgesPerSecond;               // this defines how smooth the ribbon is. A low value may produce a lot of edges.
        float edgeLifetime;                 // the length aka Lifespan. in seconds
        float gravity;                      // use arcsin(val) to get the emission angle in degree
        uint16_t textureRows;               // tiles in texture
        uint16_t textureCols;
        M2Track<uint16_t> texSlotTrack;
        M2Track<uint8_t> visibilityTrack;
        int16_t priorityPlane;
        uint16_t _;
    };
}
