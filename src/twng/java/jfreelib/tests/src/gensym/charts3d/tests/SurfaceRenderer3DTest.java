package gensym.charts3d.tests;

import gensym.charts.j3d.*;
import gensym.charts.j3d.renderers.*;
import gensym.charts.j3d.primitives.*;
import junit.framework.TestCase;

/**
 *  Tests SurfaceRenderer3D class
 */
public class SurfaceRenderer3DTest extends TestCase {

    /**
     * Tests SurfaceRenderer3D all functionality
     */
    public final void testSurfaceRenderer3D() {
        int subsets = 2;
        int points = 2;
        SurfaceRenderer3D rendererCopy = new SurfaceRenderer3D();
        SurfaceRenderer3D renderer = new SurfaceRenderer3D(rendererCopy);
        Object3D object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(2, 2, false),
                SurfaceRenderer3D.SURFACE_AND_SHADING, Renderer3D.DETAILS_FULL);

        assertNotNull(object);
        assertEquals(subsets * points / 2, object.getPrimitivesCount());

        testPrimitive(object.getPrimitive(0), new Point3D(0.0D, 1.0D, 0.0D));
        testPrimitive(object.getPrimitive(1), new Point3D(0.0D, 1.0D, 0.0D));

        object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(2, 2, false),
                SurfaceRenderer3D.SURFACE_AND_SHADING, Renderer3D.DETAILS_WIREFRAME);
        assertEquals(object.getPrimitive(0).getClass(), Rectangle3DPrimitive.class);

        object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(2, 2, false),
                SurfaceRenderer3D.SURFACE_AS_PIXELS, Renderer3D.DETAILS_WIREFRAME);
        assertTrue(object.getPrimitive(0) instanceof Point3DPrimitive);

        object = renderer.createObject3D(Test3DUtils.doCreateSimpleDataset(10, 10, true),
                SurfaceRenderer3D.SURFACE_WITH_CONTOURS, Renderer3D.DETAILS_FULL);
        assertEquals(object.getPrimitive(0).getClass(),Triangle3DPrimitive.class);
    }

    /**
     * Tests single primitive
     * @param primitive primitive to check
     * @param point object to compare
     */
    private final void testPrimitive(Object3DPrimitive primitive, Point3D point) {
        assertNotNull(primitive);
        assertEquals(primitive.getClass(), Triangle3DPrimitive.class);
        Triangle3DPrimitive prim = (Triangle3DPrimitive) primitive;
        assertEquals(prim.getTriangle3D().getA().getX(), point.getX());
        assertEquals(prim.getTriangle3D().getB().getY(), point.getY());
        assertEquals(prim.getTriangle3D().getC().getZ(), point.getZ());
    }
}
