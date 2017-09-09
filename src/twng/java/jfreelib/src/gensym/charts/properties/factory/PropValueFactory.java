package gensym.charts.properties.factory;

import gensym.charts.actions.SetValueActions;
import gensym.charts.properties.*;
import gensym.charts.properties.annotations.*;
import gensym.charts.properties.annotations.graph.*;
import gensym.charts.properties.annotations.line.*;
import gensym.charts.properties.annotations.table.*;
import gensym.charts.properties.axis.*;
import gensym.charts.properties.contour.*;
import gensym.charts.properties.gradients.*;
import gensym.charts.properties.hatching.*;
import gensym.charts.properties.hotspot.*;
import gensym.charts.properties.subtitles.*;
import gensym.charts.properties.plotting.*;
import gensym.charts.properties.rotation.*;
import gensym.charts.properties.bubble.*;
import gensym.charts.properties.legends.*;


import java.util.*;

/**
 * Property values factory
 */
public class PropValueFactory {

    /** IPropValue objects map */
    private static Map<String, Map<Integer, IPropValue>> values =
        new LinkedHashMap<String, Map<Integer, IPropValue>>();

    /**
     * Returns IPropValue object by property id
     * @param id property id
     * @param action action name
     * @return IPropValue object with specified id of null
     */
    public static IPropValue makeValue(int id, String action) {
        Map<Integer, IPropValue> map = values.get(action);
        if (map != null) {
            return map.get(id);
        }
        return null;
    }

    /**
     * Registers IPropValue object
     * @param value IPropValue object to be registered
     */
    public static void registerPropValue(IPropValue value, String action) {
        Map<Integer, IPropValue> map = values.get(action);
        if (map == null) {
            map = new LinkedHashMap<Integer, IPropValue>();
            values.put(action, map);
        }
        
        map.put(value.getPropId(), value);
    }

    /**
     * Returns list of names of registered objects
     * @return
     */
    public static List<String> getProperties() {
        ArrayList<String> list = new ArrayList<String>();
        for (Map<Integer, IPropValue> map: values.values()) {
            for (IPropValue prop : map.values()) {
                list.add(prop.getPropName());
            }
        }
        return list;
    }

    /**
     * Registers all known properties
     */
    static {
        // view
        registerPropValue(new AllowZoomingProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphPlusTableProperty(), SetValueActions.SetInt);
        registerPropValue(new FocalRectProperty(), SetValueActions.SetInt);

        // XYZ data
        registerPropValue(new XDataProperty(), SetValueActions.SetDoubleArray);
        registerPropValue(new YDataProperty(), SetValueActions.SetDoubleArray);
        registerPropValue(new ZDataProperty(), SetValueActions.SetDoubleArray);
        
        registerPropValue(new AppendXDataProperty(), SetValueActions.SetDoubleArray);
        registerPropValue(new AppendYDataProperty(), SetValueActions.SetDoubleArray);
        
        registerPropValue(new XDataSimpleProperty(), SetValueActions.SetDouble);
        registerPropValue(new YDataSimpleProperty(), SetValueActions.SetDouble);
        
        registerPropValue(new PointsProperty(), SetValueActions.SetInt);
        registerPropValue(new SubsetsProperty(), SetValueActions.SetInt);

        // null data
        registerPropValue(new NullDataValueXProperty(), SetValueActions.SetDouble);
        registerPropValue(new NullDataValueProperty(), SetValueActions.SetDouble);
        registerPropValue(new NullDataGapsProperty(), SetValueActions.SetInt);
        
        // subsets
        registerPropValue(new SubsetLabelProperty(), SetValueActions.SetString);
        registerPropValue(new SubsetLineTypesProperty(), SetValueActions.SetInt);
        registerPropValue(new SubsetColorsProperty(), SetValueActions.SetInt);
        
        registerPropValue(new AutoStatSubsetsProperty(), SetValueActions.SetInt);
        
        // title
        registerPropValue(new MainTitleProperty(), SetValueActions.SetString);
        registerPropValue(new MainTitleBoldProperty(), SetValueActions.SetInt);

        // subtitle
        registerPropValue(new SubtitleProperty(), SetValueActions.SetString);
        registerPropValue(new SubtitleBoldProperty(), SetValueActions.SetInt);
        registerPropValue(new SubtitleFontProperty(), SetValueActions.SetString);
        registerPropValue(new MultiSubtitlesTopProperty(), SetValueActions.SetString);
        registerPropValue(new MultiSubtitlesBottomProperty(), SetValueActions.SetString);

        // labels
        registerPropValue(new LabelBoldProperty(), SetValueActions.SetInt);
        registerPropValue(new PointLabelsProperty(), SetValueActions.SetString);
        
        // font
        registerPropValue(new FontSizeProperty(), SetValueActions.SetInt);
        
        // gradient
        registerPropValue(new BitmapGradientModeProperty(), SetValueActions.SetInt);
        registerPropValue(new QuickStyleProperty(), SetValueActions.SetInt);
        registerPropValue(new DeskGradientStartProperty(), SetValueActions.SetInt);
        registerPropValue(new DeskGradientEndProperty(), SetValueActions.SetInt);
        registerPropValue(new DeskGradientStyleProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphGradientStartProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphGradientEndProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphGradientStyleProperty(), SetValueActions.SetInt);
        
        // background/foreground
        registerPropValue(new DeskColorProperty(), SetValueActions.SetInt);
        registerPropValue(new BackgroundProperty(), SetValueActions.SetInt);
        
        // image adjust
        registerPropValue(new ImageAdjustLeftProperty(), SetValueActions.SetInt);
        registerPropValue(new ImageAdjustTopProperty(), SetValueActions.SetInt);
        registerPropValue(new ImageAdjustRightProperty(), SetValueActions.SetInt);
        registerPropValue(new ImageAdjustBottomProperty(), SetValueActions.SetInt);
        
        // pie
        registerPropValue(new ShowPieLablesProperty(), SetValueActions.SetInt);
        registerPropValue(new ShowPieZeroDataProperty(), SetValueActions.SetInt);
        registerPropValue(new ShowPieLabelsInsideProperty(), SetValueActions.SetInt);
        registerPropValue(new EnablePieTooltipsProperty(), SetValueActions.SetInt);
        registerPropValue(new PieSliceAutoExplodeProperty(), SetValueActions.SetInt);
        
        // legend
        registerPropValue(new LegendLocationProperty(), SetValueActions.SetInt);
        registerPropValue(new LegendStyleProperty(), SetValueActions.SetInt);
        registerPropValue(new ShowLegendProperty(), SetValueActions.SetInt);
        registerPropValue(new ShowPieLegendProperty(), SetValueActions.SetInt);
        
        // points
        registerPropValue(new MarkDataPointsProperty(), SetValueActions.SetInt);

        // annotations
        registerPropValue(new ShowAnnotationsProperty(), SetValueActions.SetInt);

        // graph annotations
        registerPropValue(new ShowGraphAnnotationsProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphAnnotationColorProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphAnnotationMoveableProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphAnnotationTextProperty(), SetValueActions.SetString);
        registerPropValue(new GraphAnnotationTextSizeProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphAnnotationTypeProperty(), SetValueActions.SetInt);
        registerPropValue(new GraphAnnotationXProperty(), SetValueActions.SetDoubleArray);
        registerPropValue(new GraphAnnotationYProperty(), SetValueActions.SetDoubleArray);
        registerPropValue(new GraphAnnotationXSimpleProperty(), SetValueActions.SetDouble);
        registerPropValue(new GraphAnnotationYSimpleProperty(), SetValueActions.SetDouble);
        registerPropValue(new GraphAnnotationAxisProperty(), SetValueActions.SetInt);
        
        // table annotations
        registerPropValue(new ShowTableAnnotationProperty(), SetValueActions.SetInt);
        registerPropValue(new WorkingTableProperty(), SetValueActions.SetInt);
        registerPropValue(new TaLocationProperty(), SetValueActions.SetInt);
        registerPropValue(new TaAxisLocationProperty(), SetValueActions.SetInt);
        registerPropValue(new TaTextProperty(), SetValueActions.SetString);
        registerPropValue(new TaTextSizeProperty(), SetValueActions.SetInt);
        registerPropValue(new TaColumnsProperty(), SetValueActions.SetInt);
        registerPropValue(new TaRowsProperty(), SetValueActions.SetInt);
        registerPropValue(new TaColorProperty(), SetValueActions.SetInt);
        registerPropValue(new TaBackColorProperty(), SetValueActions.SetInt);
        registerPropValue(new TaHeaderColumnProperty(), SetValueActions.SetInt);
        registerPropValue(new TaHeaderRowsProperty(), SetValueActions.SetInt);
        registerPropValue(new TaBorderProperty(), SetValueActions.SetInt);
        registerPropValue(new TaGridLineControlProperty(), SetValueActions.SetInt);
        registerPropValue(new TaColumnWidthProperty(), SetValueActions.SetInt);
        registerPropValue(new TaJustificationProperty(), SetValueActions.SetInt);
        
        // line annotations
        registerPropValue(new HorzLineAnnotationAxisProperty(), SetValueActions.SetInt);
        registerPropValue(new HorzLineAnnotationColorProperty(), SetValueActions.SetInt);
        registerPropValue(new HorzLineAnnotationProperty(), SetValueActions.SetDoubleArray);
        registerPropValue(new HorzLineAnnotationTextProperty(), SetValueActions.SetString);
        registerPropValue(new HorzLineAnnotationTypeProperty(), SetValueActions.SetInt);
        registerPropValue(new LineAnnotationTextSizeProperty(), SetValueActions.SetInt);
        registerPropValue(new ShowHorzLineAnnotationsProperty(), SetValueActions.SetInt);

        // rotation & autorotation
        registerPropValue(new DegreeOfRotationProperty(), SetValueActions.SetInt);
        registerPropValue(new ViewingHeightProperty(), SetValueActions.SetInt);
        registerPropValue(new AutoRotationProperty(), SetValueActions.SetInt);
        registerPropValue(new RotationIncrementProperty(), SetValueActions.SetInt);
        registerPropValue(new RotationSpeedProperty(), SetValueActions.SetInt);
        registerPropValue(new RotationDetailProperty(), SetValueActions.SetInt);

        // axis
        registerPropValue(new XAxisLabelProperty(), SetValueActions.SetString);
        registerPropValue(new YAxisLabelProperty(), SetValueActions.SetString);
        registerPropValue(new ZAxisLabelProperty(), SetValueActions.SetString);
        registerPropValue(new ShowYAxisProperty(), SetValueActions.SetInt);
        registerPropValue(new ManualScaleControlYProperty(), SetValueActions.SetInt);
        registerPropValue(new ManualMaxYProperty(), SetValueActions.SetDouble);
        registerPropValue(new ManualMinYProperty(), SetValueActions.SetDouble);

        registerPropValue(new DateTimeModeProperty(), SetValueActions.SetInt);
        registerPropValue(new StartTimeProperty(), SetValueActions.SetDouble);
        registerPropValue(new DeltasPerDayProperty(), SetValueActions.SetInt);
        registerPropValue(new DeltaXProperty(), SetValueActions.SetInt);
        registerPropValue(new ForceVerticalPointsProperty(), SetValueActions.SetInt);
        
        registerPropValue(new WorkingAxisProperty(), SetValueActions.SetInt);
        registerPropValue(new MultiAxesSubsetsProperty(), SetValueActions.SetInt);
        registerPropValue(new OverlapMultiAxesProperty(), SetValueActions.SetInt);
        
        registerPropValue(new TickColorProperty(), SetValueActions.SetInt);
        registerPropValue(new YAxisColorProperty(), SetValueActions.SetInt);

        registerPropValue(new XAxisScaleControlProperty(), SetValueActions.SetInt);
        registerPropValue(new YAxisScaleControlProperty(), SetValueActions.SetInt);

        // contours
        registerPropValue(new ManualContourLineProperty(), SetValueActions.SetDouble);
        
        // grid
        registerPropValue(new GridLineControlProperty(), SetValueActions.SetInt);
        registerPropValue(new GridStyleProperty(), SetValueActions.SetInt);
        
        // stacked data
        registerPropValue(new NoStackedDataProperty(), SetValueActions.SetInt);
        registerPropValue(new AllowHorzBarStackedProperty(), SetValueActions.SetInt);
        
        // hot spot
        registerPropValue(new AllowPointHotSpotsProperty(), SetValueActions.SetInt);
        registerPropValue(new AllowDataHotSpotsProperty(), SetValueActions.SetInt);
        registerPropValue(new AllowSubsetHotSpotsProperty(), SetValueActions.SetInt);
        
        // plotting methods
        registerPropValue(new PlottingMethodProperty(), SetValueActions.SetInt);
        registerPropValue(new PlottingMethodsProperty(), SetValueActions.SetInt);
        registerPropValue(new PolyModeProperty(), SetValueActions.SetInt);
        registerPropValue(new AllowRibbonProperty(), SetValueActions.SetInt);
        registerPropValue(new AllowStepProperty(), SetValueActions.SetInt);
        
        //hatching
        registerPropValue(new SubsetHatchProperty(), SetValueActions.SetInt);
        registerPropValue(new HatchBackColorProperty(), SetValueActions.SetInt);
        registerPropValue(new SliceHetchingProperty(), SetValueActions.SetInt);

        // scrolling
        registerPropValue(new ScrolingSubsetsProperty(), SetValueActions.SetInt);
        // table
        registerPropValue(new TableWhatProperty(), SetValueActions.SetInt);

        // bubble
        registerPropValue(new AllowBubbleProperty(), SetValueActions.SetInt);
        registerPropValue(new BubbleSizeProperty(), SetValueActions.SetInt);


        // other
        registerPropValue(new GraphForeColorProperty(), SetValueActions.SetInt);
        registerPropValue(new DataShadowProperty(), SetValueActions.SetInt);
        registerPropValue(new SubsetPointTypesProperty(), SetValueActions.SetInt);
        registerPropValue(new TextColorProperty(), SetValueActions.SetInt);
        registerPropValue(new BorderTypesProperty(), SetValueActions.SetInt);
    }
}
