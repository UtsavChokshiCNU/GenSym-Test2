package com.gensym.nols.data;

/**
 * Created by AdeelNayyer on 1/23/2017.
 */
public class RawDataSourceListenerStub implements RawDataSourceListener {
    public boolean DataPointsLabeledIsInvoked = false;
    public boolean DataSeriesAddedIsInvoked = false;
    public boolean DataSeriesRemovedIsInvoked = false;
    public boolean LabelCategoryAddedIsInvoked = false;
    public boolean LabelCategoryRemovedIsInvoked = false;
    public boolean LabelColorChangedIsInvoked = false;
    public boolean LabelNameChangedIsInvoked = false;
    public boolean LabelOrderChangedIsInvoked = false;
    public RawDataEvent DataPointsLabeledRawDataEvent = null;
    public RawDataEvent DataSeriesAddedRawDataEvent = null;
    public RawDataEvent DataSeriesRemovedRawDataEvent = null;
    public RawDataEvent LabelCategoryAddedRawDataEvent = null;
    public RawDataEvent LabelCategoryRemovedRawDataEvent = null;
    public RawDataEvent LabelColorChangedRawDataEvent = null;
    public RawDataEvent LabelNameChangedRawDataEvent = null;
    public RawDataEvent LabelOrderChangedRawDataEvent = null;

    @Override
    public void LabelCategoryAdded(RawDataEvent e) {
        LabelCategoryAddedIsInvoked = true;
        LabelCategoryAddedRawDataEvent = e;
    }

    @Override
    public void LabelCategoryRemoved(RawDataEvent e) {
        LabelCategoryRemovedIsInvoked = true;
        LabelCategoryRemovedRawDataEvent = e;
    }

    @Override
    public void DataPointsLabeled(RawDataEvent e) {
        DataPointsLabeledIsInvoked = true;
        DataPointsLabeledRawDataEvent = e;
    }

    @Override
    public void LabelOrderChanged(RawDataEvent e) {
        LabelOrderChangedIsInvoked = true;
        LabelOrderChangedRawDataEvent = e;
    }

    @Override
    public void LabelNameChanged(RawDataEvent e) {
        LabelNameChangedIsInvoked = true;
        LabelNameChangedRawDataEvent = e;
    }

    @Override
    public void LabelColorChanged(RawDataEvent e) {
        LabelColorChangedIsInvoked = true;
        LabelColorChangedRawDataEvent = e;
    }

    @Override
    public void DataSeriesAdded(RawDataEvent e) {
        DataSeriesAddedIsInvoked = true;
        DataSeriesAddedRawDataEvent = e;
    }

    @Override
    public void DataSeriesRemoved(RawDataEvent e) {
        DataSeriesRemovedIsInvoked = true;
        DataSeriesRemovedRawDataEvent = e;
    }
}
