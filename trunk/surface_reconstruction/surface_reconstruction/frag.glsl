uniform sampler3D myTexture;
uniform float pCoord;

uniform float multCoeff;

const vec3 bmin = vec3(0.0);
const vec3 bmax = vec3(1.0);

struct Ray {
    vec3 origin;
    vec3 direction;
};

bool IntersectBox ( in Ray ray, in vec3 minimum, in vec3 maximum, out float start, out float final) {
    vec3 OMIN = (minimum - ray.origin) / ray.direction;
    vec3 OMAX = (maximum - ray.origin) / ray.direction;

    vec3 MAX = max(OMAX, OMIN);
    vec3 MIN = min(OMAX, OMIN);

    final = min(MAX.x, min(MAX.y, MAX.z));
    start = max(max(MIN.x, 0.0), max(MIN.y, MIN.z));

    return final > start;
}

vec3 Raytrace(in Ray ray) {
    vec3 res = vec3(0.0);

    float start, final, time;

    if (IntersectBox(ray, bmin, bmax, start, final)) {
        //vec3 point = ray.origin + ray.direction * time;

        res = vec3(texture3D(myTexture, ray.origin + ray.direction * final).a);
    }

    return res;
}

void main(void) {
    //gl_FragColor = vec4 ( gl_TexCoord[0].st, 0, 1 );

    vec3 origin = vec3(0, 0, 0);
    vec3 direction = vec3(-1, 0, 0) * gl_TexCoord[0].x + vec3(0, 1, 0) * gl_TexCoord[0].y;
    
    Ray ray = Ray(origin, normalize(direction));

    gl_FragColor = vec4(Raytrace(ray), 1.0);

    gl_FragColor = vec4(texture3D(myTexture, vec4(1 - gl_TexCoord[0].t, 1 - gl_TexCoord[0].s, pCoord, 0.0)).a) * multCoeff;
    //gl_FragColor = vec4(texture3D(myTexture, vec4(1 - gl_TexCoord[0].t, 1 - gl_TexCoord[0].s, 0, 0.0)).a) * multCoeff;
}