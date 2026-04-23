import plotly.express as px
import plotly.graph_objects as go

numOfThreads = [1, 2, 4, 8, 16]
tenParticleTC = [667.02, 422.469, 350.495, 405.761, 541.6] #10 particles
twentyParticleTC = [1302.89, 729.987, 534.114, 591.271, 886.059] #20 particles
fourtyParticleTC = [2578.55, 1356.6, 826.972, 821.259, 1325.38] #40 particles
eightyParticleTC = [5092.29, 2642.86, 1575.29, 1473.66, 2351.34] #80 particles

title = "Runtime VS Number of Threads"
labels = {'x': 'Number of Threads', 'y': 'Time to Finish in Milliseconds', 'color': 'color'}
fig = px.bar(x=numOfThreads, y=tenParticleTC, title = title, labels = labels, width = 1200)
fig.update_xaxes(type='category')
fig.update_traces(width=0.4)
fig.update_layout(title_x=0.5)
fig.add_trace(go.Scatter(x=numOfThreads, y=tenParticleTC, line=dict(shape='spline'), name='Time Trend'))
fig.show()

title = "Runtime VS Number of Threads"
labels = {'x': 'Number of Threads', 'y': 'Time to Finish in Milliseconds', 'color': 'color'}
fig2 = px.bar(x=numOfThreads, y=twentyParticleTC, title = title, labels = labels, width = 1200)
fig2.update_xaxes(type='category')
fig2.update_traces(width=0.4)
fig2.update_layout(title_x=0.5)
fig2.add_trace(go.Scatter(x=numOfThreads, y=twentyParticleTC, line=dict(shape='spline'), name='Time Trend'))
fig2.show()

title = "Runtime VS Number of Threads"
labels = {'x': 'Number of Threads', 'y': 'Time to Finish in Milliseconds', 'color': 'color'}
fig3 = px.bar(x=numOfThreads, y=fourtyParticleTC, title = title, labels = labels, width = 1200)
fig3.update_xaxes(type='category')
fig3.update_traces(width=0.4)
fig3.update_layout(title_x=0.5)
fig3.add_trace(go.Scatter(x=numOfThreads, y=fourtyParticleTC, line=dict(shape='spline'), name='Time Trend'))
fig3.show()

title = "Runtime VS Number of Threads"
labels = {'x': 'Number of Threads', 'y': 'Time to Finish in Milliseconds', 'color': 'color'}
fig4 = px.bar(x=numOfThreads, y=eightyParticleTC, title = title, labels = labels, width = 1200)
fig4.update_xaxes(type='category')
fig4.update_traces(width=0.4)
fig4.update_layout(title_x=0.5)
fig4.add_trace(go.Scatter(x=numOfThreads, y=eightyParticleTC, line=dict(shape='spline'), name='Time Trend'))
fig4.show()