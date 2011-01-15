uniform sampler3D myTexture;
uniform float pCoord;

uniform float multCoeff;

const vec3 bmin = vec3(-1.0);
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

    res = vec4 ( gl_TexCoord[0].st, 0, 1 );
    if (IntersectBox(ray, bmin, bmax, start, final)) {
        vec3 point = ray.origin + ray.direction * start * 0.55;

        vec3 texCoord = vec3(1 - (point.x + 0.5) / 1.0, 1 - (point.y + 0.5) / 1.0, pCoord);
        //vec3 texCoord = vec3((ray.direction.x + 0.5) / 1.0, gl_TexCoord[0].t, 0.5);
        res = vec3(texture3D(myTexture, texCoord).a);
        //res = vec3(texture3D(myTexture, vec3(gl_TexCoord[0].ts, 0)).a);
        //res = vec3(0, start * 0.1, 0);
    }

    return res;
}

void main(void) {
    //gl_FragColor = vec4 ( gl_TexCoord[0].st, 0, 1 );

    vec3 origin = vec3(0, 0, -3.3);
    vec3 direction = vec3(1, 0, 0) * (0.5 - gl_TexCoord[0].t) + vec3(0, -1, 0) * (0.5 - gl_TexCoord[0].s) + vec3(0, 0, 1);
    
    Ray ray = Ray(origin, direction);

    gl_FragColor = vec4(Raytrace(ray), 1.0) * multCoeff;

    //gl_FragColor = vec4(texture3D(myTexture, vec4(1 - gl_TexCoord[0].t, 1 - gl_TexCoord[0].s, pCoord, 0.0)).a) * multCoeff;
    //gl_FragColor = vec4(texture3D(myTexture, vec4(1 - gl_TexCoord[0].t, 1 - gl_TexCoord[0].s, 0, 0.0)).a) * multCoeff;
}