<div class="cover" style="page-break-after:always;font-family:方正公文仿宋;width:100%;height:100%;border:none;margin: 0 auto;text-align:center;">
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:10%;">
        </br>
        <img src="https://gitee.com/Keldos-Li/picture/raw/master/img/%E6%A0%A1%E5%90%8D-%E9%BB%91%E8%89%B2.svg" alt="校名" style="width:100%;"/>
    </div>
    </br></br></br></br></br>
    <div style="width:60%;margin: 0 auto;height:0;padding-bottom:40%;">
        <img src="https://gitee.com/Keldos-Li/picture/raw/master/img/%E6%A0%A1%E5%BE%BD-%E9%BB%91%E8%89%B2.svg" alt="校徽" style="width:100%;"/>
	</div>
    </br></br></br></br></br></br></br></br>
    <span style="font-family:华文黑体Bold;text-align:center;font-size:20pt;margin: 10pt auto;line-height:30pt;">《谓尔智能宠物养成APP》</span>
    <p style="text-align:center;font-size:14pt;margin: 0 auto">CG Project </p>
    </br>
    </br>
    <table style="border:none;text-align:center;width:72%;font-family:仿宋;font-size:14px; margin: 0 auto;">
    <tbody style="font-family:方正公文仿宋;font-size:12pt;">
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">题　　目</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 基于OpenGL框架的智能宠物渲染和游戏机制构建</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">上课时间</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 周二11,12</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">授课教师</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">唐敏 </td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">姓　　名</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 王振阳，李想，高伟渊，王喆</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">学　　号</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">3190104758等 </td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">组　　别</td>
    		<td style="width:%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋"> 第十一组</td>     </tr>
    	<tr style="font-weight:normal;"> 
    		<td style="width:20%;text-align:right;">日　　期</td>
    		<td style="width:2%">：</td> 
    		<td style="width:40%;font-weight:normal;border-bottom: 1px solid;text-align:center;font-family:华文仿宋">2020.07.04</td>     </tr>
    </tbody>              
    </table>
</div>

<!-- 注释语句：导出PDF时会在这里分页 -->


# 谓尔智能宠物养成APP

<center><div style='height:2mm;'></div><div style="font-family:华文楷体;font-size:14pt;">第十一组（王振阳，李想，高伟渊，王喆）</div></center>
<center><span style="font-family:华文楷体;font-size:9pt;line-height:9mm">浙江大学计算机学院</span>
</center>
<div>
<div style="width:52px;float:left; font-family:方正公文黑体;">简　介：</div> 
<div style="overflow:hidden; font-family:华文楷体;">谓尔是在2021年开发的一款ios移动应用，通过交互和情感投入转化参数实现宠物养成，通过宠物开展社交，打造模糊社交新模态。
通过谓尔，你可以定制并长期培养自己的专属宠物，通过喂养日记，语音交互，提供定位和健康运动信息，甚至使用其他应用等信息让你的宠物逐渐成长，你的「一举一动」都会对宠物产生影响，使其作出反应，毛玻璃下富于变化的宠物形象满足你的情感需求。
同时，用户可以进入社交模式，在社区中随机浏览和临时领养他人宠物，通过观察和喂养宠物感受宠物主人的生活方式和性格情感，并在社交模式中完成任务解锁特殊成就，崭新的社交形式赋予模糊社交更多可能。
社交模式还支持点对点的宠物长期绑定机制，在绑定机制下，宠物有着更丰富的交互模式，以及允许进行跌倒检测、屏幕时间监控等以满足亲子家庭等关系的特殊需求。</div>
</div>
<div>
<div style="width:52px;float:left; font-family:方正公文黑体;">关键词：</div> 
<div style="overflow:hidden; font-family:华文楷体;">电子宠物；OpenGL；定制化；数字生成艺术</div>
</div>

## 谓尔的模块设计

![](assets/struct.png)

​    可以看到，APP分为若干模块，本报告仅对其中的图形学模块进行详细的阐述。其中对于大作业要求的若干条目，APP和PC端小游戏满足了如下要求。

- 具有基本体素(立方体、球、柱体、锥体、多面棱柱、多面棱台）的建模表达能力;

- 具有基本三维网格导入导出功能（建议OBJ格式) ;
	- 需要了解OBJ格式，完成基本OBJ模型的读入和导出，不要求处理文件中的纹理和材质信息；
	
- 具有基本材质、纹理的显示和编辑能力;

- 具有基本几何变换功能(旋转、平移、缩放等)﹔

- 基本光照明模型要求，并实现基本的光源编辑（如调整光源的位置，光强等参数);

- 能对建模后场景进行漫游如Zoom In/Out, Pan, Orbit,Zoom To Fit等观察功能。

- 能够提供动画播放功能(多帧数据连续绘制)，能够提供屏幕截取/保存功能。
	- 多帧连续绘制指读取连续的 obj 文件(或其他格式的模型文件)，对其网格进行多次的绘制;简单的平移、旋转、缩放等不能视为动画播放。


​    此外，APP还实现了如下的Bonus：
- 基于可选择的 AABB 碰撞盒和 OBB 碰撞盒实现的实时碰撞检测；

- 多平台支持：在 `iOS`设备上基于 `OpenGL ES`框架实现了电子宠物的交互，在 `PC` 端支持 `Window`s ，`Linux`和 `OSX` 系统，基于 `cmakelist` 进行文件组织，实现了多平台的兼容；
	
- 基于核心的物理引擎，实现了较有难度的一类吃豆人游戏。
	
	

## 谓尔基本模块实现

### 类图

```mermaid
classDiagram
      Object3D <|-- Model
      Object3D <|-- Camera
      Object3D <|-- Light
      Object3D : -vec3 position
      Object3D : -quat rotation
      Object3D : -vec3 scale
      Object3D: +getFront()
      Object3D: +getUp()
      Object3D: +getRight()
      Object3D: +getModelMatrix()
      class Model{
          -vector<vertex> vertices
          -vector<int32> indices
          -GLuint vao
          -GLuint vbo
          -GLuint ebo
          +draw()
      }
      class Camera{
          +getViewMatrix()
          +getProjectionMatrix()
          +getPosition()
      }
      class Light{
          - float intensity
          - vec3 color
      }
      Model <|-- ModelEntity
      Model <|-- ElementEntity
      class ModelEntity {
          + setParams()
          - unique_ptr shader
          - unique_ptr texture
          - struct material
      }
      class ElementEntity {
          + setParams()
          - unique_ptr shader
          - unique_ptr texture
          - struct material
          - struct base_params
      }
      ElementEntity <|-- Ball
      ElementEntity <|-- Cubic
      ElementEntity <|-- Cylinder
      ElementEntity <|-- Cone
      ElementEntity <|-- Prism

```

各个元素之间的继承派生关系如图。可以看到，在代码组织中，我们使用 `Entity` 抽象出单个元素，将所有的 `Shader`，`Texture`，`Material` 封装于其中。通过构造函数传递参数的方式指定元素需要的所有参数，并且在需要绘制的时候直接调用 `draw()`，抽象逻辑层次。对于元素进行改变完全由场景进行管理和计算。


### 场景管理

首先，场景的初始配置文件由一个 `json` 文件指定。`json` 文件的格式如下：

```json
{
    "skybox" : [
        "${leftImgPath}",
        "${rightImgPath}",
        "${upImgPath}",
        "${downImgPath}",
        "${frontImgPath}",
        "${backImgPath}"
    ],
    "camera" : {
        "position" : "${vec3}",
        "rotation" : "${vec3}"
    },
    "light" : {
        "totalNum" : "${totalNum}",
        "lightEntity" : [
            {
                "type" : "direcct",
                "position" : "${vec3}",
                "rotation" : "${vec3}",
                "insensity" : "${float}",
                "color" : "${vec3}"
            },
            {
                "type" : "direcct",
                "position" : "${vec3}",
                "rotation" : "${vec3}",
                "insensity" : "${float}",
                "color" : "${vec3}"
            }
        ]
    },
    "EntityNum" : "${EntityNum}",
    "Entity" : [
        {
            "type" : "Model|Element",
            "objFilePaht" : "${filePath}",
            "position" : "${vec3}",
            "rotation" : "${vec3}",
            "scale" : "${float}",
            "material" : "${struct}",
            "texture" : "${struct}"
        }
    ]
    
}

```

`json` 由


### 读取 obj 序列
（锟斤拷）

### 物理模型
（锟斤拷）

### 游戏机制
在PC版中我们设计了一个小游戏，小游戏的机制是，小精灵在场景内游走，在游走过程中小精灵会与场景内的体素发生碰撞并吃掉，吃掉的同时小精灵的身体会长大。

这个小游戏的实现主要分为三部分。

第一部分是开始时随机生成一定数量的体素供小球吞食。

```
for (int i = 0; i < _amount1; ++i) {

		_balls[i].reset(new Ball(0.05f));
		_cubics[i].reset(new Cubic(1.0f));
		_ellipsoids[i].reset(new Ellipsoid(0.3f, 1.0f, 2.0f));
		_cylinders[i].reset(new Cylinder(0.5f,0.6f));
		_cones[i].reset(new Cone(1.0f,1.6f));
		_prisms[i].reset(new Prism(1.5f,0.6f,6));

		float angle = (float)i / _amount1 * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		_elementPositions[i].x = _position.x+sin(angle) * radius+displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		
		_elementPositions[i].y = displacement * 0.2f;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		_elementPositions[i].z = _position.z+sin(angle) * radius+displacement;
		
		// scale
		_elementScales[i] = glm::vec3(1.0f, 1.0f, 1.0f);
		// rotate
		float rotAngle = 1.0f * (rand() % 360);
		_elementRotations[i] = glm::angleAxis(rotAngle, axis)* rotation;
	}
```

 第二部分是对场景内的小球遍历，对小球位置进行判断，如果小球坐标与小精灵所在的范围相重合，则将小球位置设置在天空盒外，同时修改小精灵的scale，否则则按一开始生成的位置信息将小球绘制出来。

```
_balls[i].get()->setDirectionalLight(_direction1,_color1,_intensity1);
		_balls[i].get()->setSpotLight(_direction,_color,_intensity,_angle,_kc,_kl,_kq);
		_balls[i].get()->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
		
		_balls[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
		_balls[i].get()->setRotation(_elementRotations[i]); 
		_balls[i].get()->setScale(_elementScales[i]); 
		

		if (-0.005<_balls[i].get()->getPosition().x<0.005 &&
		 -0.005<_balls[i].get()->getPosition().y < 0.005 ){
		//   -0.005<_balls[i].get()->getPosition().z < 0.01
			_balls[i].get()->setPosition(glm::vec3(0.0,0.0,10000.0));
			_elementPositions[i]=glm::vec3(0.0,0.0,10000.0);
			change+=0.05;
			radius1 +=0.5;

		// } else if (_models[count]->getPosition().x-0.0001<_balls[i].get()->getPosition().x<_models[count]->getPosition().x+0.0001 && _models[count]->getPosition().y-0.0001<_balls[i].get()->getPosition().y<_models[count]->getPosition().y+0.0001 && _models[count]->getPosition().z-0.0001<_balls[i].get()->getPosition().z<_models[count]->getPosition().z+0.0001) {
		// 	_balls[i].get()->setPosition(_elementPositions[i]);
		}else{
			_balls[i].get()->draw(projection, view, viewPos);
		}
```

第三部分是将场景内体素与相机绑定，通过体素跟随相机运动实现与小精灵在场景中移动的效果，从而简化了对小精灵坐标的计算，使小精灵实际上始终保持在坐标(0,0,0)处。

```
balls[i].get()->setPosition(glm::vec3(_cameras[0]->position.x+_elementPositions[i].x,_cameras[0]->position.y+_elementPositions[i].y,_cameras[0]->position.z+_elementPositions[i].z-15)); 
```

场景开始和短暂漫游后的对比：
显而易见的，结束时小精灵体积显著增大，场景中小球数量减少。
<img width="1392" alt="对比-开始" src="https://user-images.githubusercontent.com/71428910/124621537-f15bd280-deac-11eb-80a3-c86313179593.png">
<img width="1392" alt="对比-结束" src="https://user-images.githubusercontent.com/71428910/124621543-f3259600-deac-11eb-806a-b30cb7cc8e9e.png">


## PC 端效果演示

1 基本体素（立方体、球、圆柱、圆锥、多面棱柱、多面棱台）的建模表达能力

体素的基类为ElementEntity，该基类为对Element类（Element类继承了object3d类）的封装，构造函数（根据vertices和indices构造）和draw函数里都调用了Element类的构造函数根据vertices和indices构造）和draw函数。

每个构造函数代码的结构均类似，先计算出每个三角形面片的3个顶点（vertices）和对应绘制顺序（indices）,再调用进行构造，再设置shader，，再根据构造函数的参数设置scale，绘制时统一调用基类ElementEntity的draw函数进行绘制。

以下依次说明各个类的vertices和indices计算方法：

以下依次为球、椭球、立方体、圆柱、圆锥、多面棱柱的类定义，每个类分别有特定的构造函数可以根据指定的参数进行构造。默认的position和rotation均为object3d中的默认值，scale按照构造函数接收的参数设置。构造函数的参数依次为：

![图片 1](https://user-images.githubusercontent.com/71428910/124619665-6c23ee00-deab-11eb-8eb7-6951fc4999a5.png)

球：半径radius

顶点位置、法向量（顶点位置-原点位置（0,0,0））、纹理坐标（贴图均匀分格采样）

```C++
for (int y = 0; y <= segments; y++)
	{
		for (int x = 0; x <= segments; x++)
		{
			Vertex vertex{};
			float xSegment = (float)x / (float)segments;
			float ySegment = (float)y / (float)segments;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			vertex.position.x = xPos;
			vertex.position.y = yPos;
			vertex.position.z = zPos;
			vertex.normal.x = xPos;
			vertex.normal.y = yPos;
			vertex.normal.z = zPos;
			vertex.texCoord.x = 1 - xSegment;
			vertex.texCoord.y = 1 - ySegment;
			vertices.push_back(vertex);
		}
	}
```

绘制顺序

```c++
//indices
	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j + 1);
		}
	}
	_element.reset(new Element(vertices, indices));
```

![图片 2](https://user-images.githubusercontent.com/71428910/124619725-7940dd00-deab-11eb-8d96-0ec59be16396.png)

椭球：xyz三个轴的长度xaxis，yaxis，zaxis。

```
	for (int y = 0; y <= segments; y++)
	{
		for (int x = 0; x <= segments; x++)
		{
			Vertex vertex{};
			float xSegment = (float)x / (float)segments;
			float ySegment = (float)y / (float)segments;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			vertex.position.x = xPos;
			vertex.position.y = yPos;
			vertex.position.z = zPos;
			vertex.normal.x = xPos;
			vertex.normal.y = yPos;
			vertex.normal.z = zPos;
			vertex.texCoord.x = 1 - xSegment;
			vertex.texCoord.y = 1 - ySegment;
			vertices.push_back(vertex);
		}
	}

	//indices
	for (int i = 0; i < segments; i++)
	{
		for (int j = 0; j < segments; j++)
		{
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j);
			indices.push_back((i + 1) * (segments + 1) + j + 1);
			indices.push_back(i * (segments + 1) + j + 1);
		}
	}
	_element.reset(new Element(vertices, indices));
```

![图片 3](https://user-images.githubusercontent.com/71428910/124619692-7219cf00-deab-11eb-9414-9d02d6e3b9f4.png)

立方体：边长size

六个面的三角形顶点坐标和纹理坐标（每个面一张贴图）

```C++
	static const float position[6][6][5] = {
		// left
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		// right
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

		// top
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,

		// bottom
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		// front
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,

		// back
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	};

	
```

法向量

```
static const float normals[6][3] = {
		{ -1, 0, 0 },
		{ +1, 0, 0 },
		{ 0, +1, 0 },
		{ 0, -1, 0 },
		{ 0, 0, +1 },
		{ 0, 0, -1 }
	};
```

绘制

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	for (int i = 0; i < 6; i++) {
		for (int v = 0; v < 6; v++) {
			Vertex vertex{};
			vertex.position.x = position[i][v][0];
			vertex.position.y = position[i][v][1];
			vertex.position.z = position[i][v][2];
			vertex.normal.x = normals[i][0];
			vertex.normal.y = normals[i][1];
			vertex.normal.z = normals[i][2];
			vertex.texCoord.x = 1 - position[i][v][3];
			vertex.texCoord.y = 1 - position[i][v][4];
			vertices.push_back(vertex);
			indices.push_back(indice);
			indice++;
		}
	}
	
	_element.reset(new Element(vertices, indices));

![图片 6](https://user-images.githubusercontent.com/71428910/124620022-b016f300-deab-11eb-98c5-9fed4c3af63b.png)

圆柱：底面圆的半径radius，高度height

分成上圆面、中间柱面、下圆面三部分绘制

上圆面（法向量朝上，圆面贴图）

std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	int sidecount = 36;
	float y = height / 2.0;
	

	//up circle
	Vertex vertexup{};
	vertexup.position.x = 0;
	vertexup.position.y = y;
	vertexup.position.z = 0;
	vertexup.normal.x = 0;
	vertexup.normal.y = 1;
	vertexup.normal.z = 0;
	vertexup.texCoord.x = 0.5;
	vertexup.texCoord.y = 0.5;
	
	for (int i = sidecount; i >= 0; --i) {
		float angle = i / (float)sidecount * PI * 2;
		vertices.push_back(vertexup);
		indices.push_back(indice);
		indice++;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	
		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}

中间柱面（法向量水平向外，柱面贴图）

```
	//bottom circle
	Vertex vertexdown{};
	y = -height / 2.0;
	vertexdown.position.x = 0;
	vertexdown.position.y = y;
	vertexdown.position.z = 0;
	vertexdown.normal.x = 0;
	vertexdown.normal.y = -1;
	vertexdown.normal.z = 0;
	vertexdown.texCoord.x = 0.5;
	vertexdown.texCoord.y = 0.5;
	for (int i = 0; i <= sidecount; ++i) {
		vertices.push_back(vertexdown);
		indices.push_back(indice);
		indice++;

		float angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = y;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
```

下圆面（法向量朝下，圆面贴图）

		//middle rectangles
		float yup = height / 2.0;
		float ydown = -height / 2.0;
		for (int i = 0; i <= sidecount; ++i) {
			GLfloat angle = i / (float)sidecount * PI * 2;
			Vertex vertex{};
			vertex.position.x = cos(angle) * radius;
			vertex.position.y = yup;
			vertex.position.z = sin(angle) * radius;
			vertex.normal.x = cos(angle) * radius;
			vertex.normal.y = 0;
			vertex.normal.z = sin(angle) * radius;
			vertex.texCoord.x = 1 - i / (float)sidecount;
			vertex.texCoord.y = 1;
			vertices.push_back(vertex);
			indices.push_back(indice);
			indice++;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	
		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	
		angle = i / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - i / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	
		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = yup;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 1;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = cos(angle) * radius;
		vertex.normal.y = 0;
		vertex.normal.z = sin(angle) * radius;
		vertex.texCoord.x = 1 - (i + 1) / (float)sidecount;
		vertex.texCoord.y = 0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	
	_element.reset(new Element(vertices, indices));


![图片 4](https://user-images.githubusercontent.com/71428910/124619850-92e22480-deab-11eb-8d9f-247083df9836.png)

圆锥：底面圆的半径radius，高度height

只需在圆柱代码上稍作改动，减少一个上圆面的绘制，中间柱面改为由从上顶点到下圆面的三角形组成的圆锥面。

下圆面（法向量朝下，圆面贴图）

```c++
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	uint32_t indice = 0;
	int sidecount = 36;

	//bottom circle
	Vertex vertexdown{};
	float yup = height / 2.0;
	float ydown = -height / 2.0;
	vertexdown.position.x = 0;
	vertexdown.position.y = ydown;
	vertexdown.position.z = 0;
	vertexdown.normal.x = 0;
	vertexdown.normal.y = -1;
	vertexdown.normal.z = 0;
	vertexdown.texCoord.x = 0.5;
	vertexdown.texCoord.y = 0.5;
	for (int i = 0; i <= sidecount; ++i) {
		vertices.push_back(vertexdown);
		indices.push_back(indice);
		indice++;

		float angle = i / (float)sidecount * PI * 2;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = -1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}

	//uppoint
	Vertex vertexup{};
	vertexup.position.x = 0;
	vertexup.position.y = yup;
	vertexup.position.z = 0;
	vertexup.normal.x = 0;
	vertexup.normal.y = 1;
	vertexup.normal.z = 0;
	vertexup.texCoord.x = 0.5;
	vertexup.texCoord.y = 0.5;
	for (int i = sidecount; i >= 0; --i) {
		float angle = i / (float)sidecount * PI * 2;
		vertices.push_back(vertexup);
		indices.push_back(indice);
		indice++;
		Vertex vertex{};
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;

		angle = (i + 1) / (float)sidecount * PI * 2;
		vertex.position.x = cos(angle) * radius;
		vertex.position.y = ydown;
		vertex.position.z = sin(angle) * radius;
		vertex.normal.x = 0;
		vertex.normal.y = 1;
		vertex.normal.z = 0;
		vertex.texCoord.x = (cos(angle) + 1) / 2.0;
		vertex.texCoord.y = (sin(angle) + 1) / 2.0;
		vertices.push_back(vertex);
		indices.push_back(indice);
		indice++;
	}
	
	_element.reset(new Element(vertices, indices));
```

![图片 5](https://user-images.githubusercontent.com/71428910/124619811-8cec4380-deab-11eb-9579-b0b09dfe5243.png)

多面棱柱：底面多边形的半径radius，高度height，多面棱柱的面数facenum（3,4,5……）

和圆柱一模一样，因为圆柱相当于面数为无穷大的多面棱柱，只需将圆柱代码中的sidecount设为面数facenum即可。

```c++
int sidecount = facenum;
```
2 场景漫游

场景漫游通过在entity中调用camera类，分别利用WASD进行方向控制，同时采用鼠标点按拖拽。

```c++
if (_keyboardInput.keyStates[GLFW_KEY_W] != GLFW_RELEASE) {
		std::cout << "W" << std::endl;
		camera->position += camera->getFront()*_cameraMoveSpeed;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_A] != GLFW_RELEASE) {
		std::cout << "A" << std::endl;
		camera->position -= glm::normalize(glm::cross(camera->getFront(), camera->getUp())) * _cameraRotateSpeed*3.0;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_S] != GLFW_RELEASE) {
		std::cout << "S" << std::endl;
		camera->position -= camera->getFront()*_cameraMoveSpeed;
	}

	if (_keyboardInput.keyStates[GLFW_KEY_D] != GLFW_RELEASE) {
		std::cout << "D" << std::endl;
		camera->position += glm::normalize(glm::cross(camera->getFront(), camera->getUp())) * _cameraRotateSpeed*3.0;
	}

	if (_mouseInput.move.xCurrent != _mouseInput.move.xOld) {
		if (_mouseInput.click.left == true){
		std::cout << "mouse move in x direction" << std::endl;
		const float angle = -_cameraRotateSpeed * _deltaTime * (_mouseInput.move.xCurrent - _mouseInput.move.xOld);
		const glm::vec3 axis1 = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 axis2 = camera->getRight();
		angle1 -= angle;
		camera->rotation = { glm::cos(angle * 0.5f),axis2[0] * glm::sin(angle2*0.5f) , axis1[1] * glm::sin(angle1*0.5f)+ axis2[1] * glm::sin(angle1* 0.5f), 0.0f };
		}
		_mouseInput.move.xOld = _mouseInput.move.xCurrent;
	}

	if (_mouseInput.move.yCurrent != _mouseInput.move.yOld) {
		if (_mouseInput.click.left == true){
		std::cout << "mouse move in y direction" << std::endl;
		/* write your code here */
		// rotate around local right
		const float angle = -_cameraRotateSpeed * _deltaTime * (_mouseInput.move.yCurrent - _mouseInput.move.yOld);
		const glm::vec3 axis1 = { 0.0f, 1.0f, 0.0f };
		const glm::vec3 axis2 = camera->getRight();
		// you should know how quaternion works to represent rotation
		// camera->rotation = ...
		angle2 -= angle;
		camera->rotation = { glm::cos(angle * 0.5f),axis2[0] * glm::sin(angle2*0.5f) , axis1[1] * glm::sin(angle1*0.5f) + axis2[1] * glm::sin(angle1* 0.5f), 0.0f };
		}
		_mouseInput.move.yOld = _mouseInput.move.yCurrent;
	}
```
漫游效果：
<img width="1392" alt="截屏2021-07-05 下午7 15 53" src="https://user-images.githubusercontent.com/71428910/124620178-d341a280-deab-11eb-9b7e-b5223986fed3.png">
<img width="1391" alt="截屏2021-07-05 下午7 16 15" src="https://user-images.githubusercontent.com/71428910/124620185-d50b6600-deab-11eb-827c-c6c66470eb66.png">

3 几何变换

几何变换体现在所有的图形上

其中重点以背景planet的生成为例介绍几何变换。

因为图形学中生成的球体实际上是一个多面体，因此当多个球体叠加时会出现花纹交叠的特性，正是利用这一特性我们生成了背景的灯球：即通过三个相同坐标但旋转轴不同的球体，对其贴上颜色较复杂的贴图然后按各自轴转动，即产生了相应效果。

创建planet数组，并利用rand()随机生成旋转角度

```
for (int i = 0; i < 3; ++i) {
	_planets[i].reset(new ModelEntity(filepath,blendTexturePaths5,blendTexturePaths6));
	}
```

```
float rotAngle = 1.0f * (rand() % 360);
_elementRotations[i] = glm::angleAxis(rotAngle, axis)* rotation;
```

绘制

```
for (int i= 0;i<3;i++){
		const glm::vec3 axis1 = glm::vec3(1.0f, 0.0f, 0.0f);	
		_elementRotations[i] *= glm::angleAxis(angle, axis1);

		_planets[i]->setDirectionalLight(_direction1,_color1,_intensity1);
		_planets[i]->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
		_planets[i]->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);


		_planetPosition = glm::vec3(_cameras[0]->position.x+200,_cameras[0]->position.y+200,_cameras[0]->position.z-1000);
		_planets[i]->setRotation(_elementRotations[i]);
		_planets[i]->setScale(glm::vec3(400.0,400.0,400.0));
		_planets[i]->setPosition(_planetPosition);
		_planets[i]->draw(projection, view, viewPos);
	}

```
效果如下
<img width="642" alt="截屏2021-07-06 下午10 46 10" src="https://user-images.githubusercontent.com/71428910/124620415-0421d780-deac-11eb-93e5-21f149874fd3.png">

4 贴图和光照

基本体素等均用到了贴图，其中最主要的就是小精灵的眼睛与身体贴图混合

整个场景采用了冯光照和贴图混合的形式，同时采用diretionalLight和spotLight两种光照，均可用通过GUI进行编辑。

片段着色器代码如下：

```
const char* fragCode =
		"#version 330 core\n"
		"in vec3 FragPos;\n"
		"in vec3 Normal;\n"
		"in vec2 TexCoord;\n"
		"out vec4 color;\n"

		"struct DirectionalLight {\n"
		"	vec3 direction;\n"
		"	vec3 color;\n"
		"	float intensity;\n"
		"};\n"

		"struct SpotLight {\n"
		"	vec3 position;\n"
		"	vec3 direction;\n"
		"	float intensity;\n"
		"	vec3 color;\n"
		"	float angle;\n"
		"	float kc;\n"
		"	float kl;\n"
		"	float kq;\n"
		"};\n"

		"struct Material {\n"
		"	vec3 albedo;\n"
		"	float ka;\n"
		"	vec3 kd;\n"
		"	vec3 ks;\n"
		"	float ns;\n"
		"	float blend;\n"
		"};\n"

		"// uniform variables\n"
		"uniform Material material;\n"
		"uniform DirectionalLight directionalLight;\n"
		"uniform SpotLight spotLight;\n"
		"uniform vec3 viewPos;\n"
		"uniform float depth;\n"
		"uniform sampler2D mapKd1;\n"
		"uniform sampler2D mapKd2;\n"

		"vec3 calcDirectionalLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(-directionalLight.direction);\n"
		"// diffuse color\n" 
		"	vec3 diffuse = directionalLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"// specular color\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	vec3 specular = directionalLight.color * pow(max(dot(viewDir, reflectDir), 0.0f), material.ns) * material.ks;\n"
		"	return directionalLight.intensity * diffuse + directionalLight.intensity * specular ;\n"
		"}\n"

		"vec3 calcSpotLight(vec3 normal) {\n"
		"	vec3 lightDir = normalize(spotLight.position - FragPos);\n"
		"	float theta = acos(-dot(lightDir, normalize(spotLight.direction)));\n"
		"	if (theta > spotLight.angle) {\n"
		"		return vec3(0.0f, 0.0f, 0.0f);\n"
		"	}\n"
		"	vec3 diffuse = spotLight.color * max(dot(lightDir, normal), 0.0f) * material.kd;\n"
		"// specular color\n"
		"	vec3 viewDir = normalize(viewPos - FragPos);\n"
		"	vec3 reflectDir = reflect(-lightDir, normal);\n"
		"	vec3 specular = spotLight.color * pow(max(dot(viewDir, reflectDir), 0.0f), material.ns) * material.ks;\n"
		"	float distance = length(spotLight.position - FragPos);\n"

		"	float attenuation = 1.0f / (spotLight.kc + spotLight.kl * distance + spotLight.kq * distance * distance);\n"
		"	return spotLight.intensity * attenuation * diffuse + spotLight.intensity * attenuation * specular;\n"
		"}\n"

		"void main() {\n"
		"	vec3 ambient = material.ka * material.albedo;\n"
		"	vec3 normal = normalize(Normal);\n"
    	"	float blur = 0.0;\n"
 
    	"	float far_distance = 10.0;\n"
    	"	float far_plane = 0.0;\n"
 
        "	blur = clamp(depth, far_plane - far_distance, far_plane);\n"
        "	blur = (far_plane - blur) / far_distance;\n"

		"	// diffuse color\n"
		"	vec3 diffuse = calcDirectionalLight(normal);\n"
		"	vec4 tex = mix(texture(mapKd1, TexCoord), texture(mapKd2, TexCoord), material.blend);\n"
		"	color = vec4(ambient + diffuse, 1.0f) * tex;\n"
		"	color.a = blur;\n"
		"}\n";
```

由于shader被写在modelEntity和elementEntity中，为了能通过Entity类的参数来控制光照变化，我们专门设置了几个函数用于传输和编辑相关数值

```
void setDirectionalLight(glm::vec3 direction,glm::vec3 color,float intensity);
void setSpotLight(glm::vec3 position,glm::vec3 direction,glm::vec3 color,float intensity, float angle, float kc, float kl,float kq);
void setMaterial(glm::vec3 albedo,float ka,glm::vec3 kd,glm::vec3 ks, float ns,float blend);
```

具体的使用和GUI控制如下：

```
_body->setDirectionalLight(_direction1,_color1,_intensity1);
	_body->setSpotLight(_lightPosition,_direction,_color,_intensity,_angle,_kc,_kl,_kq);
	_body->setMaterial(_albedo,_ka,_kd,_ks,_ns,_blend);
```

```
ImGui::Text("Render Mode");

		ImGui::Text("directional light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##1", &_intensity1, 0.0f, 2.0f);
		ImGui::ColorEdit3("color##1", (float*)&_color1);
		ImGui::NewLine();

		ImGui::Text("spot light");
		ImGui::Separator();
		ImGui::SliderFloat("intensity##2", &_intensity, 0.0f, 5.0f);
		ImGui::ColorEdit3("color##2", (float*)&_color);
		ImGui::SliderFloat("angle##2", (float*)&_angle, 0.0f, glm::radians(180.0f), "%f rad");
		ImGui::NewLine();

		ImGui::Text("Material");
		ImGui::Separator();
		ImGui::ColorEdit3("albedo", (float*)&_albedo);
		ImGui::SliderFloat("ka", &_ka, 0.0f, 1.0f);
		ImGui::ColorEdit3("kd", (float*)&_kd);
		ImGui::ColorEdit3("ks", (float*)&_ks);
		ImGui::SliderFloat("ns", &_ns, 0.0f, 50.0f);
		ImGui::SliderFloat("blend", &_blend, 0.0f, 1.0f);

		ImGui::End();
```
天空盒、通过修改GUI参数改变了场景中各体素的光照贴图等效果如下：
<img width="1392" alt="截屏2021-07-05 下午6 38 20" src="https://user-images.githubusercontent.com/71428910/124621198-a8a41980-deac-11eb-8aa7-a559d3d32751.png">
<img width="1392" alt="截屏2021-07-06 下午10 50 16" src="https://user-images.githubusercontent.com/71428910/124621204-a9d54680-deac-11eb-9be0-8242a5f1e15e.png">
<img width="1392" alt="截屏2021-07-06 下午10 49 15" src="https://user-images.githubusercontent.com/71428910/124621214-ab9f0a00-deac-11eb-9cdd-5b16df8ff425.png">
<img width="1392" alt="截屏2021-07-05 下午6 39 38" src="https://user-images.githubusercontent.com/71428910/124621222-acd03700-deac-11eb-88df-4ed64d17223b.png">


## iOS 端效果演示

### iOS 端设计

### iOS 端效果

## 进一步的产品原型
（锟斤拷）
## 附录
（锟斤拷）
